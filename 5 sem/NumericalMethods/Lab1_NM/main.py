import numpy
import math

epsilon = 0.001
rangeMin = -4.0
rangeMax = 1.0

def f(x):
    return x**3 + 6 * x**2 + 9 * x + 2

def fi(x):
    return -1 * (x**3 + 6 * x**2 + 2)/9

def f_derivative(x):
    return -1 * (x**2 / 3) - 4 * (x / 3)
def to_fixed(num):
    return f"{num:.{16}f}"

def fixedPointIteration(x):
    step_1 = 1
    N = 15
    while True:
        x1 = fi(x)
        step_1 += 1
        if numpy.fabs(f(x1)) <= epsilon:
            break
        print("Iteration ", step_1, " x1 = ", x1, " and f(x1) ", f(x1))
        temp = x
        x = x1
        count = step_1
        if(step_1 >= N):
            break

def findMaxValue(x1, x2):
    maximum = 0
    i = x1
    while i < x2:
        maximum = f_derivative(i) if f_derivative(i) > maximum else maximum
        i += epsilon
    return maximum

def relaxationMethod():
    fda = abs(f_derivative(rangeMin))
    fdb = abs(f_derivative(rangeMax))
    min1 = fdb if fda > fdb else fda
    max1 = math.ceil(findMaxValue(rangeMin, rangeMax))
    print("Min: ", min1, "Max: ", max1)
    x = rangeMax
    previous= 100
    z0 = abs(x)
    q = (max1 - min1)/(max1 + min1)
    t0 = 2/(max1 + min1)
    n = int(numpy.log(abs(z0)/epsilon)/numpy.log(1/q)) + 1
    fx = f(x)

    results = [[x,to_fixed(fx)]]
    while abs(previous - x) >= epsilon:
        previous = x
        x = previous - t0 * f(previous)
        fx = f(x)
        results.append([x, to_fixed(fx)])

    print("A priory mark: ", n)
    print("A posteriori mark: ", len(results))
    print("n \t| xn \t\t\t| f(xn) \t\t|")

    for i in range(len(results)):
        print(i, "\t|", results[i][0], "\t|", results[i][1], "\t|")


print("============Simple Iteration Method==============")
fixedPointIteration(rangeMax)
# print("\n==================Relaxation Method==============")
# relaxationMethod()