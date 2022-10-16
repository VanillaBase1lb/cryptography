from random import SystemRandom
import random
import numpy as np
import math

seed_values = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
num_of_intervals = 10
lower_bound = 1
upper_bound = 200
num_of_samples = 5000
expected_value = num_of_samples / num_of_intervals
randval1 = 10.117  # for 95%confidence interval
randval2 = 7.633  # for 99%confidence interval

for seed_x in seed_values:
    np.random.seed(seed_x)
    random_int = np.random.randint(
        low=lower_bound, high=upper_bound, size=(num_of_samples)
    )
    observed_count = np.zeros(num_of_intervals)
    expected_count = np.full(
        shape=num_of_intervals, fill_value=int(expected_value), dtype=int
    )
    for i in random_int:
        observed_count[math.floor((i - 1) / (upper_bound / num_of_intervals))] = (
            observed_count[math.floor((i - 1) / (upper_bound / num_of_intervals))] + 1
        )
    result = (
        ((observed_count - expected_count) * (observed_count - expected_count))
        / expected_count
    ).sum()

    def final_conclusion(result):
        if result < randval1:
            return "Random"
        else:
            return "Not Random"

    def final_conclusion_1(result):
        if result < randval2:
            return "Random"
        else:
            return "Not Random"

    finalresult = {
        "chisqaure value": "{:.3f}".format(result),
        "table value": randval1,
        "alpha value": 0.05,
        "conclusion": final_conclusion(result),
    }
    finalresult1 = {
        "chisqaure value": "{:.3f}".format(result),
        "table value": randval2,
        "alpha value": 0.01,
        "conclusion": final_conclusion_1(result),
    }
    finaloutput = {
        "For 95% confidence interval": finalresult,
        "For 99% confidence interval": finalresult1,
    }
    print("seed_x", seed_x)
    for i in finaloutput:

        print(i, finaloutput[i])
    print("\n")

print("\nfor System random\n")

for seed_x in seed_values:
    random_int = np.zeros(num_of_samples)
    for i in range(num_of_samples):
        random_int[i] = random.SystemRandom(seed_x).randrange(1, 200)
    observed_count = np.zeros(num_of_intervals)
    expected_count = np.full(
        shape=num_of_intervals, fill_value=int(expected_value), dtype=int
    )
    for i in random_int:
        observed_count[math.floor((i - 1) / (upper_bound / num_of_intervals))] = (
            observed_count[math.floor((i - 1) / (upper_bound / num_of_intervals))] + 1
        )
    result = (
        ((observed_count - expected_count) * (observed_count - expected_count))
        / expected_count
    ).sum()

    def final_conclusion(result):
        if result < randval1:
            return "Random"
        else:
            return "Not Random"

    def final_conclusion_1(result):
        if result < randval2:
            return "Random"
        else:
            return "Not Random"

    finalresult = {
        "chisqaure value": "{:.3f}".format(result),
        "table value": randval1,
        "alpha value": 0.05,
        "conclusion": final_conclusion(result),
    }
    finalresult1 = {
        "chisqaure value": "{:.3f}".format(result),
        "table value": randval2,
        "alpha value": 0.01,
        "conclusion": final_conclusion_1(result),
    }
    finaloutput = {
        "For 95% confidence interval": finalresult,
        "For 99% confidence interval": finalresult1,
    }
    print("seed_x", seed_x)
    for i in finaloutput:

        print(i, finaloutput[i])
    print("\n")
