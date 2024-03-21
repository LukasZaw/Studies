import numpy as np

data = np.genfromtxt("1111.dat")

y_values = np.unique(data[:, 1])

for y in y_values:
    subset = data[data[:, 1] == y][:, 2]

    avg = np.mean(subset)

    median = np.median(subset)

    dev = np.std(subset)

    print(f"Średnia dla y = {y}: {avg}")
    print(f"Mediana dla y = {y}: {median}")
    print(f"Odchylenie standardowe dla y = {y}: {dev}")
    print()
