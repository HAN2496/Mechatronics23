import time
import matplotlib.pyplot as plt
import numpy as np
import random

dt = 0.005

def calc_itae(time, current_position, target_position):
    return time * abs(current_position - target_position) * dt


current_time = 0
trial_num = 6
target_arr = [5, -3, -2, -2, 4, 0]
time_arr = [5, 6, 2, 3, 4, 5]
time_arr = [5, 11, 13, 16, 20, 25]
error = 0
current_position = 0

tmp = 0
while current_time <= 25:
    current_time += dt
    if tmp >= 6:
        break
    while time_arr[tmp] > current_time:
        error += calc_itae(current_time, current_position, target_arr[tmp])
        current_position += 6.25 * dt
    tmp += 1

print(error)