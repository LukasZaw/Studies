import numpy as np
import sympy as sp


def f(x):
    return 255.78150562770563 * x - 127.58033896103898


def calkPr(a, b, n):
    h = (b - a) / n
    x = np.zeros(n + 1)
    y = np.zeros(n + 1)

    for i in range(n + 1):
        x[i] = a + i * h
        y[i] = f(x[i])

    c = 0

    for i in range(n + 1):
        c += h * (y[i])
    return c


a = 0
b = 2

X = sp.symbols("x")
cd = sp.integrate(f(X), (X, a, b))


for n in range(1, 5000):
    c1 = calkPr(a, b, n)
    E = (c1 - cd) / cd * 100
    if abs(E) < 0.1:
        print(n)
        break

print("Calka - aproksymacyjna:")
print(calkPr(a, b, n))
