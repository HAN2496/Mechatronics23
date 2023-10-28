import time
import matplotlib.pyplot as plt
import numpy as np

LOOPTIME = 0.001
PULSETIME = 5

class Motor:
    def __init__(self):
        self.position = 0  # 모터의 현재 위치
        self.max_update = 100

    def update_position(self, input_value):
        # 간단한 모델: 입력값에 따라 위치 변경
        self.position += input_value / 16
        # 실제 모터 모델은 더 복잡할 수 있음


class PIDController:
    def __init__(self, kp, ki, kd, target_arr):
        self.motor = Motor()

        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.target_arr = target_arr
        self.initialize()

    def update(self, target_point, current_position):
        self.time += LOOPTIME
        error = self.target_arr[target_point] - current_position
        self.integral += error
        derivative = error - self.previous_error

        output = self.kp * error + self.ki * self.integral + self.kd * derivative
        self.previous_error = error

        self.total_error += LOOPTIME * np.abs(error) * (self.time - 5 * target_point)

        if output >= self.motor.max_update:
            return self.motor.max_update

        return output

    def initialize(self):
        self.previous_error = 0
        self.integral = 0
        self.total_error = 0
        self.time = 0
        self.total_error = 0


if __name__ == "__main__":
    motor_pos_arr = []
    # PID 파라미터 설정
    kp = 10
    ki = 0.05
    kd = 0.01

    for i in range(999, 1000):

        target_position = [8]

        # PID 컨트롤러 및 모터 초기화
        pid = PIDController(kp, ki, kd, target_arr=target_position)
        motor = Motor()

        t = 0
        step = 0
        # 시뮬레이션 루프
        for idx, target_point in enumerate(target_position):
            while t <= 5 * (idx + 1):
                step += 1
                t += LOOPTIME
                motor_input = pid.update(idx, motor.position)
                motor.update_position(motor_input)
                motor_pos_arr.append([t, motor.position])
        pid.initialize()

    motor_pos_arr = np.array(motor_pos_arr)
    plt.scatter(motor_pos_arr[:, 0], motor_pos_arr[:, 1])
    plt.show()
