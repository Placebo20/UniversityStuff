import math
import numpy

def function1(x, y):
    return math.sin(x) + 2 * y - 1.6
def function2(x, y):
    return math.cos(y - 1) - 1
def function1DX(x, y):
    return math.cos(x)
def function2DX(x, y):
    return 0
def function1DY(x,y):
    return 2
def function2DY(x,y):
    return math.cos(y - 1)

def checkAbs(num):
    maxNum = abs(num[0])
    for i in num:
        if abs(i) > maxNum:
            maxNum = abs(i)
    return maxNum

def newtonMethodModified(SIZE):
    epsilon = 0.000001
    x0 = [1] * SIZE  # початкове наближення
    # обчислюємо матрицю Якобі
    a = numpy.array([[function1DX(x0[0], x0[1]), function1DY(x0[0], x0[1])],
                     [function2DX(x0[0], x0[1]), function2DY(x0[0], x0[1])]])
    # обчислємо рівняння
    f = numpy.array([function1(x0[0], x0[1]), function2(x0[0], x0[1])])



    #обчислюємо нове наближення
    x1 = x0 - numpy.linalg.inv(a) @ f

    while checkAbs(x1 - x0) >= epsilon:  # умова припинення ітераційного процессу
        x0 = x1
        a = numpy.array([[function1DX(x1[0], x1[1]), function1DY(x1[0], x1[1])],
                         [function2DX(x1[0], x1[1]), function2DY(x1[0], x1[1])]])
        f = numpy.array([function1(x1[0], x1[1]), function2(x1[0], x1[1])])
        x1 = x0 - numpy.linalg.inv(a) @ f
    print("Roots of a system of nonlinear equations with eigenvalues: ",x1)
    print(f"First function check: {function1(x1[0], x1[1]):9.10f}")
    print(f"Second function check: {function2(x1[0], x1[1]):9.10f}")

def degreeMethod(aMatrix, xMatrix, n):
    epsilon = 0.001
    maxIter = 10000
    lambdaOld = 1.0
    cond = True
    step = 1
    while cond:
        xMatrix = numpy.matmul(aMatrix, xMatrix)
        lambdaNew = min(abs(xMatrix))
        xMatrix = xMatrix / lambdaNew
        print(f'[{step}] Eigenvalue = %0.4f' % lambdaNew)
        step += 1
        error = abs(lambdaNew - lambdaOld)
        if step > maxIter: # умова припинення
            break
        lambdaOld = lambdaNew
        cond = error > epsilon

print("------------------First Task------------------")
SIZE = 2
newtonMethodModified(SIZE)
print()
print("------------------Second Task------------------")
a = numpy.array([[5,-1,1,-1],[-1, 15, -1, 1],[1, -1, 15, -1],[-1, 1, -1, 15]])
x = numpy.array([15,5,-9,15])
degreeMethod(a, x, a.shape[0])