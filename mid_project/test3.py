import time
import matplotlib.pyplot as plt
import numpy as np

LOOPTIME = 0.001
PULSETIME = 5

class Motor:
    def __init__(self):
        self.position = 0
        self.max_update = 100

    def