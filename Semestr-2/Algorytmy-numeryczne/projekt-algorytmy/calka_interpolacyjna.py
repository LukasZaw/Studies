import numpy as np
import sympy as sp


def f(x):
    return (
        58.30410476190477
        + 117.05914559083985 * x * (x - 0.0)
        - 18.734671751219533 * x * (x - 0.0) * (x - 0.1)
        - 0.7463783693451443 * x * (x - 0.0) * (x - 0.1) * (x - 0.2)
        + 2.168102827487625 * x * (x - 0.0) * (x - 0.1) * (x - 0.2) * (x - 0.3)
        + 1.1389523809523379
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        - 4.619987772589941
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        - 31.258898645777293
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        + 118.68238050584586
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        + 46.551393329044366
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        + 40.04248571428572
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        + 46.55139332904474
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        + 118.68238050584564
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        - 31.258898645777123
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        - 4.619987772589866
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        + 1.1389523809526303
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        * (x - 1.4)
        + 2.168102827487441
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        * (x - 1.4)
        * (x - 1.5)
        - 0.7463783693448737
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        * (x - 1.4)
        * (x - 1.5)
        * (x - 1.6)
        - 18.73467175121949
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        * (x - 1.4)
        * (x - 1.5)
        * (x - 1.6)
        * (x - 1.7)
        + 117.0591455908395
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        * (x - 1.4)
        * (x - 1.5)
        * (x - 1.6)
        * (x - 1.7)
        * (x - 1.8)
        + 58.30410476190477
        * x
        * (x - 0.0)
        * (x - 0.1)
        * (x - 0.2)
        * (x - 0.3)
        * (x - 0.4)
        * (x - 0.5)
        * (x - 0.6)
        * (x - 0.7)
        * (x - 0.8)
        * (x - 0.9)
        * (x - 1.0)
        * (x - 1.1)
        * (x - 1.2)
        * (x - 1.3)
        * (x - 1.4)
        * (x - 1.5)
        * (x - 1.6)
        * (x - 1.7)
        * (x - 1.8)
        * (x - 1.9)
    )


def calkTr(a, b, n):
    h = (b - a) / n
    x = np.zeros(n + 1)
    y = np.zeros(n + 1)
    for i in range(n + 1):
        x[i] = a + i * h
        y[i] = f(x[i])

    c = 0

    for i in range(n):
        c += h * ((y[i] + y[i + 1]) / 2)
    return c


a = 0
b = 2
# n = 4999

X = sp.symbols("x")
cd = sp.integrate(f(X), (X, a, b))


for n in range(1, 5000):
    c2 = calkTr(a, b, n)
    E2 = (c2 - cd) / cd * 100
    if abs(E2) < 0.1:
        break

print("Calka - interpolacyjna:")
print(calkTr(a, b, n))