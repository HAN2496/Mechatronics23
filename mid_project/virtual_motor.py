import time
import matplotlib.pyplot as plt
import numpy as np
import random

# Constants
LOOPTIME = 0.001  # 5 milliseconds
ENC2REDGEAR = 235.78
MAX_SPEED = 6.25 / 5  # Maximum motor speed
REFERENCE_POSITION = 10

class Motor:
    def __init__(self, max_speed):
        self.speed = 0  # Motor speed
        self.max_speed = max_speed  # Maximum motor speed

    def set_speed(self, speed):
        # Limit the speed to the maximum speed
        self.speed = max(min(speed, self.max_speed), -self.max_speed)

class Encoder:
    def __init__(self):
        self.position = 0  # Encoder position

    def update_position(self, motor_speed, enc_to_red_gear):
        # Simulate encoder position change
        self.position += motor_speed
        return self.position / enc_to_red_gear

class PIDController:
    def __init__(self, p_gain, i_gain, d_gain):
        self.p_gain = p_gain
        self.i_gain = i_gain
        self.d_gain = d_gain
        self.integral = 0
        self.previous_error = 0

    def calculate(self, error):
        dt = LOOPTIME
        # Integral part
        self.integral += error * dt
        integral_term = self.i_gain * self.integral

        # Derivative part
        derivative = (error - self.previous_error) / dt
        derivative_term = self.d_gain * derivative

        # Proportional part
        proportional_term = self.p_gain * error

        # Update the previous error for the next derivative calculation
        self.previous_error = error

        # Calculate total control signal
        control_signal = proportional_term + integral_term + derivative_term
        return control_signal

def run_test(reference_positions, duration_per_position, motor, encoder, pid_controller):
    positions = []
    errors = []
    time_stamps = []
    ref_positions_array = []
    virtual_time = 0  # Initialize virtual time

    for ref_pos in reference_positions:
        end_time = virtual_time + duration_per_position  # Set the end time for the current reference position

        while virtual_time < end_time:
            # PID Control
            red_gear_position = encoder.update_position(motor.speed, ENC2REDGEAR)
            error_position = ref_pos - red_gear_position
            control_signal = pid_controller.calculate(error_position)
            motor.set_speed(control_signal)

            # Logging
            positions.append(red_gear_position)
            errors.append(error_position)
            time_stamps.append(virtual_time)
            ref_positions_array.append(ref_pos)

            # Update virtual time
            virtual_time += LOOPTIME

    return time_stamps, positions, errors, ref_positions_array

# Test Parameters
test_size = random.randint(5, 9)  # Random test size between 5 and 9
test_size = 1
test_positions = random.sample(range(-8, 9), test_size)  # Random positions
test_positions = np.array([20])
test_duration = 5  # 5 seconds for each test position

print(f"test position: {test_positions}")
ITAE_arr = []

PGAIN, IGAIN, DGAIN = 600, 10, 50

motor = Motor(MAX_SPEED)
encoder = Encoder()
pid_controller = PIDController(PGAIN, IGAIN, DGAIN)

time_stamps, positions, errors, ref_positions_array = run_test(test_positions, test_duration, motor, encoder, pid_controller)

# Calculate and display ITAE score
itae_score = sum(np.abs(errors) * np.array(time_stamps)) * LOOPTIME
print(f"ITAE Score: {itae_score:.2f}")
ITAE_arr.append(np.array([PGAIN, IGAIN, DGAIN, itae_score]))

plt.figure(figsize=(10, 6))
plt.plot(time_stamps, positions, label='Gear Position')
plt.plot(time_stamps, ref_positions_array, 'r--', label='Reference Position')

plt.xlabel('Time (s)')
plt.ylabel('Position')
plt.title(f'ITAE: {itae_score}, D: {DGAIN}')
plt.legend()
plt.show()

ITAE_arr = np.array(ITAE_arr)
print(ITAE_arr)
