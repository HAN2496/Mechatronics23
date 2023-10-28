import time
import matplotlib.pyplot as plt
import numpy as np

LOOPTIME = 0.001

class Motor:
    def __init__(self):
        self.position = 0  # 모터의 현재 위치
        self.velocity_max = 6.25

    def update_position(self, input_value):
        # 간단한 모델: 입력값에 따라 위치 변경
        self.position += input_value
        # 실제 모터 모델은 더 복잡할 수 있음


class PIDController:
    def __init__(self, kp, ki, kd, target_arr):
        self.motor = Motor()

        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.target_arr = target_arr

        self.previous_error = 0
        self.integral = 0
        self.total_error = 0
        self.time = 0

    def update(self, target_point, current_position):
        error = target_point - current_position
        self.integral += error
        derivative = error - self.previous_error

        output = self.kp * error + self.ki * self.integral + self.kd * derivative
        self.previous_error = error

        if output >= self.motor.velocity_max:
            return self.motor.velocity_max

        self.total_error += LOOPTIME * np.abs(error) * ()

        return output


if __name__ == "__main__":

    # PID 파라미터 설정
    kp = 0.1
    ki = 0.05
    kd = 0.01

    target_position = [0, 3, 10]

    # PID 컨트롤러 및 모터 초기화
    pid = PIDController(kp, ki, kd, target_arr=target_position)
    motor = Motor()
    motor_pos_arr = []

    t = 0
    # 시뮬레이션 루프
    for step in range(100):
        t += LOOPTIME
        motor_input = pid.update(target_position, motor.position)
        motor.update_position(motor_input)

        print(f"Step {step}, Motor Position: {motor.position}")
        motor_pos_arr.append([t, motor.position])
        time.sleep(LOOPTIME)

    motor_pos_arr = np.array(motor_pos_arr)
    plt.scatter(motor_pos_arr[:, 0], motor_pos_arr[:, 1])
    plt.show()