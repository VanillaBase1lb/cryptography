import platform
import os
import random
import math
import scipy.stats

import numpy as np

print("Name of the operating system:" + os.name)
print("Name of the OS system:" + platform.system())
print("Version of the operating system:" + platform.release())

seed_int = [23, 29, 64, 109, 243, 91, 73, 9, 11, 45, 87, 101, 131]

# intervals=10
range_low = 0
range_high = 5
total_size = 30
value_for_30_dof_005 = 0.24170
value_for_30_dof_001 = 0.28988
# expected_value=total_size/intervals

for seed_x in seed_int:
    np.random.seed(seed_x)
    # random_int = np.random.rand(total_size)
    # random_int=random_int*5
    random_int = np.random.uniform(0, 5, total_size)
    random_int.sort()
    dplus = np.zeros(total_size)
    dminus = np.zeros(total_size)
    for i in range(total_size):
        dplus[i] = ((i + 1) / total_size) - (random_int[i] / (range_high - range_low))
        dminus[i] = (random_int[i] / (range_high - range_low)) - (i / total_size)
    result = max(dplus.max(), dminus.max())
    # print(result)
    print("For 95% Confidence Interval")
    if result < value_for_30_dof_005:
        print("Random")
    else:
        print("Not Random")

    print("For 99% Confidence Interval")
    if result < value_for_30_dof_001:
        print("Random")
    else:
        print("Not Random")

for seed_x in seed_int:
    # random.seed(seed_x)
    random_int = np.zeros(total_size)
    for i in range(total_size):
        random_int[i] = random.SystemRandom(seed_x).uniform(range_low, range_high)
    random_int.sort()
    dplus = np.zeros(total_size)
    dminus = np.zeros(total_size)
    for i in range(total_size):
        dplus[i] = ((i + 1) / total_size) - (random_int[i] / (range_high - range_low))
        dminus[i] = (random_int[i] / (range_high - range_low)) - (i / total_size)
    result = max(dplus.max(), dminus.max())
    # print(result)
    print("For 95% Confidence Interval")
    if result < value_for_30_dof_005:
        print("Random")
    else:
        print("Not Random")

    print("For 99% Confidence Interval")
    if result < value_for_30_dof_001:
        print("Random")
    else:
        print("Not Random")
