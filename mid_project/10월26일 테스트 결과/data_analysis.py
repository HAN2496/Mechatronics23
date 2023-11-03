import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

LOOPTIME = 5
def calc_itae(time, error, current):
    return time * abs(error - current) * LOOPTIME

df = pd.read_csv('150-1-1.csv')
df_time = df.iloc[:, 0]
df_pos = df.iloc[:, 1]
df_vel = df_pos.diff()[1:] / 0.001

plt.scatter(df_time, df_pos)
plt.show()

