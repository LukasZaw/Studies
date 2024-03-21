import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("1111.dat")
X = data[:21, 0]
Y = data[:21, 2]


# Interpolacja Lagrange'a
def interpolacja_lagrange(X, Y):
    n = X.size
    A = np.zeros(n)
    for i in range(n):
        mianownik = 1
        for j in range(n):
            if i != j:
                mianownik *= X[i] - X[j]
        A[i] = Y[i] / mianownik
    return A


# Interpolacja trygonometryczna
def interpolacja_trygonometryczna(X, Y):
    n = X.size
    A = np.zeros(n)
    for k in range(n):
        suma = 0
        for j in range(n):
            suma += Y[j] * np.cos(2 * np.pi * k * X[j] / X[-1])
        A[k] = suma / n
    return A


# Obliczenie współczynników interpolacji
wspolczynniki_lagrange = interpolacja_lagrange(X, Y)
wspolczynniki_trygonometryczna = interpolacja_trygonometryczna(X, Y)


# Generowanie wyrażenia wielomianowego
def wielomian(A, X):
    n = A.size
    wynik = ""
    for i in range(n):
        if A[i] != 0:
            if i == 0:
                wynik += f"{A[i]}"
            else:
                wynik += f'{" + " if A[i] > 0 else " - "}{abs(A[i])} * x'
                for j in range(i):
                    wynik += f" * (x - {X[j]})"
    return wynik


# Interpolacja trygonometryczna
X_interp = np.linspace(X[0], X[-1], 200)
Y_interp_tryg = np.zeros_like(X_interp)
for i in range(X_interp.size):
    for k in range(X.size):
        Y_interp_tryg[i] += wspolczynniki_trygonometryczna[k] * np.cos(
            2 * np.pi * k * X_interp[i] / X[-1]
        )

wielomian_lagrange = wielomian(wspolczynniki_lagrange, X)
wielomian_trygonometryczna = wielomian(wspolczynniki_trygonometryczna, X)

print("Wielomian interpolacyjny (Lagrange):")
print(wielomian_lagrange)
print("Wielomian interpolacyjny (Trygonometryczna):")
print(wielomian_trygonometryczna)

plt.figure()
plt.plot(X, Y, label="Interpolacja Lagrange'a", color="green")
plt.scatter(X, Y, label="Punkty wejściowe", color="blue")


plt.plot(X_interp, Y_interp_tryg, label="Interpolacja trygonometryczna", color="red")


plt.xlabel("os X")
plt.ylabel("oś Y")
plt.title("Interpolacja Lagrange'a vs Interpolacja trygonometryczna")
plt.legend()
plt.grid(True)
plt.show()
