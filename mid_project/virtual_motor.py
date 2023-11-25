import time
import matplotlib.pyplot as plt
import numpy as np
import random

# Constants
LOOPTIME = 0.005  # 5 milliseconds
ENC2REDGEAR = 235.78
MAX_SPEED = 6.25  # Maximum motor speed
REFERENCE_POSITION = 10

class Motor:
    def __init__(self, max_speed):
        self.speed = 0  # Motor speed
        self.max_speed = max_speed  # Maximum motor speed

    def set_speed(self, speed):
        # Limit the speed to the maximum speed
        speed = speed / 100 * 6.25
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
        self.m1 = 0
        self.e1 = 0
        self.e2 = 0

    def calculate(self, error):
        dt = LOOPTIME
        g1 = self.p_gain + self.i_gain * dt + self.d_gain / dt
        g2 = - self.p_gain - 2 * self.d_gain / dt
        g3 = self.d_gain / dt
        m = self.m1 + g1 * error + g2 * self.e1 + g3 * self.e2
        self.e2 = self.e1
        self.e1 = error
        self.m1 = m

        return m

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

def evaluate_data(time_stamps, positions, error, ref_position):
    pass


# Test Parameters
test_size = random.randint(5, 9)  # Random test size between 5 and 9
test_size = 1
test_positions = random.sample(range(-8, 9), test_size)  # Random positions
test_positions = np.array([5])
test_duration = 30  # 5 seconds for each test position

print(f"test position: {test_positions}")
ITAE_arr = []
plt.figure(figsize=(10,6))

for i in range(5):
    gain = [0, 0.1, 1, 10, 100]
    PGAIN, IGAIN, DGAIN = 200, 0.1, gain[i]

    motor = Motor(MAX_SPEED)
    encoder = Encoder()
    pid_controller = PIDController(PGAIN, IGAIN, DGAIN)

    time_stamps, positions, errors, ref_positions_array = run_test(test_positions, test_duration, motor, encoder, pid_controller)

    # Calculate and display ITAE score
    itae_score = sum(np.abs(errors) * np.array(time_stamps)) * LOOPTIME
    print(f"ITAE Score: {itae_score:.2f}")
    ITAE_arr.append([PGAIN, IGAIN, DGAIN, itae_score])

    plt.plot(time_stamps, positions, label=f'P: {PGAIN}, I: {IGAIN}, D: {DGAIN}, ITAE: {round(itae_score, 3)}', linewidth=2)


    plt.legend()

plt.plot(time_stamps, ref_positions_array, 'r--', label='Reference Position')
plt.xlabel('Time (s)')
plt.ylabel('Position')
plt.title(f'Virtual Motor Test - P Gain')
ITAE_arr = np.array(ITAE_arr)
print(ITAE_arr)
plt.show()

