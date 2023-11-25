import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def calc_itae():
    pass


df = pd.read_csv("23_2.csv")
time = df.iloc[:, 0]
pos = df.iloc[:, 1]
i0d0 = df.iloc[5::100, :]
plt.plot(time, pos, label='P: 800, I: 0.2, D: 0', linewidth=3)


df = pd.read_csv("23_1.csv")
time = df.iloc[:, 0]
pos = df.iloc[:, 1]
plt.plot(time, pos, label='P: 800, I: 0.2, D: 50', linewidth=3)
plt.legend()
plt.title('Test Result')
plt.xlabel('Time (s)')
plt.ylabel('Position')
plt.show()
