import numpy as np
import matplotlib.pyplot as plt

m = 11
n = 21


def f(x, y):
    return 255.78150562770563 * x - 127.58033896103898


def fx(x, y):
    return 255.78150562770563


def pochodne(m, n):
    x = np.linspace(0, 2, n)
    y = np.linspace(0, 3, m)
    x, y = np.meshgrid(x, y)
    z = np.zeros((m, n))
    zxA = np.zeros((m, n))

    for i in range(m):
        for j in range(n):
            z[i][j] = f(x[i][j], y[i][j])
            zxA[i][j] = fx(x[i][j], y[i][j])

    zx = np.zeros(n)
    pzxA = zxA[1]
    pz = z[1]
    px = x[1]

    for i in range(n):
        if i == 0:
            zx[i] = (pz[i + 1] - pz[i]) / (px[i + 1] - px[i])
        elif i == n - 1:
            zx[i] = (pz[i] - pz[i - 1]) / (px[i] - px[i - 1])
        else:
            zx[i] = (pz[i + 1] - pz[i - 1]) / (px[i + 1] - px[i - 1])

    zxx = np.zeros(n)

    for i in range(n):
        if i == 0:
            zxx[i] = (zx[i + 1] - zx[i]) / (px[i + 1] - px[i])
        elif i == n - 1:
            zxx[i] = (zx[i] - zx[i - 1]) / (px[i] - px[i - 1])
        else:
            zxx[i] = (zx[i + 1] - zx[i - 1]) / (px[i + 1] - px[i - 1])

    pzxA = zxA[1]
    Rpx = zx - pzxA

    return Rpx


print(pochodne(m, n))

wyniki_poch = pochodne(m, n)

data = np.loadtxt("136699.dat")
x = data[:, 0]


def check_monotonicity(x, wyniki_poch):
    n = len(x)

    monotonicity = ""

    for i in range(n - 1):
        if wyniki_poch[i] < wyniki_poch[i + 1]:
            monotonicity_new = "rosnaca"
        elif wyniki_poch[i] > wyniki_poch[i + 1]:
            monotonicity_new = "malejaca"
        else:
            monotonicity_new = "stala"

        if monotonicity_new != monotonicity:
            if monotonicity != "":
                print(f"Funkcja jest {monotonicity}: od {start} do {end}")
            start = x[i]

        end = x[i + 1]
        monotonicity = monotonicity_new

    if monotonicity != "":
        print(f"Funkcja jest {monotonicity}: od {start} do {end}")


print(check_monotonicity(x, wyniki_poch))

plt.plot(x, wyniki_poch, label="f'(x)")
plt.xlabel("x")
plt.ylabel("f'(x)")
plt.title("Wykres pochodnej f'(x)")


plt.legend()
plt.show()
