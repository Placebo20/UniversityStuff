import numpy as np
from numpy.polynomial import polynomial as p
from numpy.polynomial import Polynomial as P
import matplotlib.pyplot as plt


def f(x):
    return 2 ** -x + x ** 3 - 20


def get_divided_diffs(y, h):
    div_diffs = np.zeros((y.size, y.size))
    div_diffs[:, 0] = y

    for i in range(1, y.size):
        for j in range(0, y.size - i):
            div_diffs[j, i] = (div_diffs[j, i - 1] - div_diffs[j + 1, i - 1]) / (-h * i)

    return div_diffs


def get_spline(y, x):
    tridiag_a = np.zeros((x.size - 2, x.size - 2))
    b = np.empty(x.size - 2)

    for i in range(0, x.size - 2):
        b[i] = (y[i + 2] - y[i + 1]) / (x[i + 2] - x[i + 1]) - (y[i + 1] - y[i]) / (x[i + 1] - x[i])
        if i > 0:
            tridiag_a[i, i - 1] = (x[i + 1] - x[i]) / 6
        tridiag_a[i, i] = (x[i + 2] - x[i]) / 3
        if i < x.size - 3:
            tridiag_a[i, i + 1] = (x[i + 2] - x[i + 1]) / 6

    m = np.linalg.solve(tridiag_a, b)
    m = np.insert(m, 0, 0)
    m = np.insert(m, m.size, 0)

    polys = []

    for i in range(0, x.size - 1):
        poly = P([0])
        h = x[i + 1] - x[i]
        poly += P([x[i + 1], -1]) ** 3 * (m[i] / (6 * h))
        poly += P([-x[i], 1]) ** 3 * (m[i + 1] / (6 * h))
        poly += P([x[i + 1], -1]) * ((y[i] - m[i] * h * h / 6) / h)
        poly += P([-x[i], 1]) * ((y[i + 1] - m[i + 1] * h * h / 6) / h)

        polys.append(poly.coef)

    return polys

n = 10
x_value = np.linspace(-4, 4, n)
y_value = f(x_value)

real = np.linspace(-4, 4, 100)


def quadratic_graph(scatter_x, scatter_y):
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax.spines['left'].set_position('center')
    ax.spines['bottom'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.xaxis.set_ticks_position('bottom')
    ax.yaxis.set_ticks_position('left')
    plt.scatter(scatter_x, scatter_y)


print("Natural cubic splines:")

spline_polys = get_spline(y_value, x_value)

quadratic_graph(x_value, y_value)
for i in range(0, n - 1):
    x_lower = -4 + (8 / (n-1)) * i
    x_upper = -4 + (8 / (n-1)) * (i+1)
    x_interval = np.linspace(x_lower, x_upper, 50)
    print("{0} for [{1}; {2}]".format(spline_polys[i], x_lower, x_upper))
    plt.plot(x_interval, p.polyval(x_interval, spline_polys[i]))
plt.show()