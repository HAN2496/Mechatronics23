import time
import matplotlib.pyplot as plt
import numpy as np

LOOPTIME = 0.001

class Motor:
    def __init__(self):
        self.position = 0  # 모터의 현재 위치
        self.velocity_max = 100

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
        self.initialize()

    def update(self, target_point, current_position):
        self.time += LOOPTIME
        error = self.target_arr[target_point] - current_position
        self.integral += error
        derivative = error - self.previous_error

        output = self.kp * error + self.ki * self.integral + self.kd * derivative
        self.previous_error = error

        if output >= self.motor.velocity_max:
            return self.motor.velocity_max

        self.total_error += LOOPTIME * np.abs(error) * (self.time - 5 * target_point)
        return output

    def initialize(self):
        self.previous_error = 0
        self.integral = 0
        self.total_error = 0
        self.time = 0
        self.total_error = 0


if __name__ == "__main__":
    error_arr = []
    # PID 파라미터 설정
    kp = 0.1
    ki = 0.05
    kd = 0.01

    for i in range(1000):
        kp += i / 2

        target_position = [8, -4, 3]
    
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
            error_arr.append([kp, pid.total_error])
        pid.initialize()

    error_arr = np.array(error_arr)
    print(np.shape(error_arr))
    min = np.min(error_arr[:, 1])
    print(f"Minimum: {min} / Index: {np.where(error_arr==min)[0]}")
    plt.scatter(error_arr[:, 0], error_arr[:, 1])
    plt.show()

