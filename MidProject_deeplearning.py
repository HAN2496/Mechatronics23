import time

class Motor:
    def __init__(self):
        self.position = 0  # 모터의 현재 위치
        self.velocity_max = 1

    def update_position(self, input_value):
        # 간단한 모델: 입력값에 따라 위치 변경
        self.position += input_value
        # 실제 모터 모델은 더 복잡할 수 있음


class PIDController:
    def __init__(self, kp, ki, kd):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.previous_error = 0
        self.integral = 0

    def update(self, set_point, current_position):
        error = set_point - current_position
        self.integral += error
        derivative = error - self.previous_error

        output = self.kp * error + self.ki * self.integral + self.kd * derivative
        self.previous_error = error

        return output


# PID 파라미터 설정
kp = 0.1
ki = 0.05
kd = 0.01

# PID 컨트롤러 및 모터 초기화
pid = PIDController(kp, ki, kd)
motor = Motor()

# 목표 위치 설정
target_position = 10

# 시뮬레이션 루프
for step in range(100):
    motor_input = pid.update(target_position, motor.position)
    motor.update_position(motor_input)

    print(f"Step {step}, Motor Position: {motor.position}")
    time.sleep(0.1)
