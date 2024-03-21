import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata

data = np.loadtxt("1111.dat")

x_values = data[:, 0]
y_values = data[:, 1]
z_values = data[:, 2]

x_unique = np.linspace(min(x_values), max(x_values), 1000)
y_unique = np.linspace(min(y_values), max(y_values), 1000)
X, Y = np.meshgrid(x_unique, y_unique)

Z = griddata((x_values, y_values), z_values, (X, Y), method="linear")

plt.figure(figsize=(8, 6))
heatmap = plt.pcolormesh(X, Y, Z, cmap="jet")
plt.colorbar(heatmap)

plt.xlabel("Oś X")
plt.ylabel("Oś Y")

plt.title("Heatmapa 2D")
plt.show()
