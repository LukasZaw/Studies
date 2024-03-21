import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("1111.dat")

data = np.array(data)

x = data[:, 0]
y = data[:, 1]
z = data[:, 2]

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

ax.plot_trisurf(x, y, z, cmap="viridis")

ax.set_xlabel("Oś X")
ax.set_ylabel("Oś Y")
ax.set_zlabel("Oś Z")

plt.show()
