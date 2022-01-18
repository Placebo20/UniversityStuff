import numpy as np

with open('y4.txt') as file:
    data = np.array([line.split() for line in file.readlines()], float).T

c3 = 0.2
c4 = 0.12
m1 = 12
m3 = 18
# c1, c2, m2 невідомі

# Матриця утворена функціяєю чутливості, використовується для оцінки невідомих параметрів за відоми спостереженнями, на часовому інтервалі
def getSensMatrix(b):
    return np.array([
        [0, 1, 0, 0, 0, 0],
        [-(b[1] + b[0]) / m1, 0, b[1] / m1, 0, 0, 0],
        [0, 0, 0, 1, 0, 0],
        [b[1] / b[2], 0, -(b[1] + c3) / b[2], 0, c3 / b[2], 0],
        [0, 0, 0, 0, 0, 1],
        [0, 0, c3 / m3, 0, -(c4 + c3) / m3, 0]
    ])

def calculateModelDerivatives(y, b):
    db0 = np.array([
        [0, 0, 0, 0, 0, 0],
        [- 1 / m1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ])

    db1 = np.array([
        [0, 0, 0, 0, 0, 0],
        [- 1 / m1, 0, 1 / m1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [1 / b[2], 0, -1 / b[2], 0, c3 / b[2], 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ])

    db2 = np.array([
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [- b[1] / (b[2] ** 2), 0, (b[1] + c3) / (b[2] ** 2), 0, -c3 / (b[2] ** 2), 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ])

    db0 = db0 @ y
    db1 = db1 @ y
    db2 = db2 @ y
    return np.array([db0, db1, db2]).T

def calculateF(y, b):
    return getSensMatrix(b) @ y

def findParameters(b, t0, T, deltaT, eps):
    timeStamps = np.linspace(t0, T, int((T - t0) / deltaT + 1))

    while True:
        # Runge-Kutta для моделі. Крок 1. Знаходимо y(t, beta0)
        yy = np.zeros_like(data)
        yy[0] = data[0].copy()
        for i in range(1, len(timeStamps)):
            y_prev = yy[i - 1]
            k1 = deltaT * calculateF(y_prev, b)
            k2 = deltaT * calculateF(y_prev + k1 / 2, b)
            k3 = deltaT * calculateF(y_prev + k2 / 2, b)
            k4 = deltaT * calculateF(y_prev + k3, b)
            y = y_prev + (k1 + 2 * k2 + 2 * k3 + k4) / 6
            yy[i] = y

        # Runge-Kutta для функції чутливості
        uu = np.zeros((len(timeStamps), 6, 3))
        db = calculateModelDerivatives(yy.T, b)
        A = getSensMatrix(b)
        for i in range(1, len(timeStamps)):
            k1 = deltaT * (A @ uu[i - 1] + db[i - 1])
            k2 = deltaT * (A @ (uu[i - 1] + k1 / 2) + db[i - 1])
            k3 = deltaT * (A @ (uu[i - 1] + k2 / 2) + db[i - 1])
            k4 = deltaT * (A @ (uu[i - 1] + k3) + db[i - 1])
            u_next = uu[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6
            uu[i] = u_next

        # знаходимо deltaB
        du = (np.array([u.T @ u for u in uu]) * deltaT).sum(0)
        du = np.linalg.inv(du)
        diff_y = (data - yy)
        uY = (np.array([uu[i].T @ diff_y[i] for i in range(len(timeStamps))]) * deltaT).sum(0)
        diff_beta = du @ uY
        b += diff_beta

        if np.abs(diff_beta).max() < eps: # умова зупинки алгоритму
            break

    return b # Наближений розв'язок задачі

if __name__ == "__main__":
    b0 = np.array([0.1, 0.08, 21]) # початкове наближення
    t0 = 0 # початок інтервалу
    T = 50 # кінець інтервалу
    deltaT = 0.2 # крок
    eps = 0.001 # параметр точності
    print("Solution is:", findParameters(b0, t0, T, deltaT, eps))