import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def calc_itae():
    pass


df = pd.read_csv("51.00-2.00-20.00 (Error- 291115.5).csv").iloc[:, 1]
plt.plot(df)
plt.show()

print(f"Total Error: {np.sum()}")