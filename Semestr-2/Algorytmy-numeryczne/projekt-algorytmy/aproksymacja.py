import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("1111.dat")
x = data[:, 0]
y = data[:, 2]


def f(x, p):
    return p[1] * x + p[0]


def aproksymacja_f1zm(x, y):
    M = np.zeros([2, 2])
    P = np.zeros([2])

    n = np.size(x)

    M[0][0] = n

    for i in range(n):
        M[0][1] += x[i]
        M[1][0] += x[i]
        M[1][1] += x[i] * x[i]
        P[0] += y[i]
        P[1] += y[i] * x[i]

    p = np.zeros(2)
    p = np.linalg.solve(M, P)

    x2 = np.linspace(0, 2, 300)
    plt.ylabel("oś Y")
    plt.xlabel("oś X")

    plt.plot(x2, f(x2, p), color="green")
    plt.plot(x, y, "x", color="blue", alpha=0.5)

    plt.show()


aproksymacja_f1zm(x, y)
