import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def calc_itae():
    pass


df = pd.read_csv("pid_itae_scores3.csv")
pgain = df.iloc[:, 0]
igain = df.iloc[:, 1]
dgain = df.iloc[:, 2]
err = df.iloc[:, 3]

i0d0 = df.iloc[5::100, :]
print(i0d0)