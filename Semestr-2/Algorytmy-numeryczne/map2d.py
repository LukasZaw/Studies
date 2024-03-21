import numpy as np
import matplotlib.pyplot as plt

np.set_printoptions(suppress=True)
# Wczytanie danych
data = np.loadtxt("1111x.dat")

x_values = data[:, 0]
y_values = data[:, 1]
z_values = data[:, 2]

# Siatka
x_unique = np.unique(x_values)
y_unique = np.unique(y_values)
X, Y = np.meshgrid(x_unique, y_unique)

# Macierz Z
Z = np.zeros((len(y_unique), len(x_unique)))
for x, y, z in zip(x_values, y_values, z_values):
    x_index = np.where(x_unique == x)[0]
    y_index = np.where(y_unique == y)[0]
    Z[y_index, x_index] = z

# Generowanie heatmapy
plt.figure(figsize=(10, 6))
heatmap = plt.pcolormesh(X, Y, Z, cmap="coolwarm")
plt.colorbar(heatmap)

plt.xlabel("Oś X")
plt.ylabel("Oś Y")

plt.title("Heatmapa 2D")
plt.show()
