import matplotlib.pyplot as plt
import numpy as np

np.set_printoptions(suppress=True)

x = np.loadtxt("1111.dat")[:, 0]
y = np.loadtxt("1111.dat")[:, 1]
z = np.loadtxt("1111.dat")[:, 2]

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection="3d")
ax.scatter(x, y, z, c="r", marker="x")

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
plt.show()
