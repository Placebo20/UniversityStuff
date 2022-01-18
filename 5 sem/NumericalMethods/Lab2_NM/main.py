import numpy

def squareRootMethod(aMatrix, bVector, eps=0.001):
    dMatrix = numpy.empty([4,4])
    sMatrix = numpy.empty([4,4])

    for i in range(aMatrix.shape[0]):
        sum = 0
        for j in range(i):
            sum += sMatrix[j][i] * sMatrix[j][i] * dMatrix[j][j]

        # Будуємо матриці sMatrix та dMatrix
        dMatrix[i][i] = numpy.sign(aMatrix[i][i] - sum);
        sMatrix[i][i] = numpy.sqrt(numpy.abs(aMatrix[i][i] - sum));

        for j in range(i + 1, aMatrix.shape[0], 1):
            sum = 0;
            for k in range(i):
                sum += sMatrix[k][i] * dMatrix[k][k] * sMatrix[k][j]

            sMatrix[i][j] = (aMatrix[i][j] - sum) / (dMatrix[i][i] * sMatrix[i][i])

    StD = numpy.transpose(sMatrix) * dMatrix

    # Рахуємо значення детермінанту
    StDS = StD * sMatrix
    print("detA = Det(StDS) =", numpy.linalg.det(StDS))

    y = numpy.empty([4])

    # дістаємо y
    for i in range(aMatrix.shape[0]):
        sum = 0
        for j in range(i):
            sum += StD[i][j] * y[j]
        y[i] = (bVector[i] - sum) / StD[i][i]
    x = numpy.empty([4])

    for i in range(aMatrix.shape[0] - 1, -1, -1):
        sum = 0
        for j in range(aMatrix.shape[0] - 1, i, -1):
            sum += sMatrix[i][j] * x[j]
        x[i] = (y[i] - sum) / sMatrix[i][i]

    return x


def yakobiMethod(aMatrix, bVector, eps=0.001):

    # Перевірка на збіжність методу
    def checkMethodConvergence():
        for i in range(0, aMatrix.shape[0]):
            sum = 0
            for j in range(0, aMatrix.shape[0]):
                if i != j:
                    sum += abs(aMatrix[i][j])
            if sum > abs(aMatrix[i][i]):
                return False
        print("The method coincides")
        return True

    if not checkMethodConvergence():
        raise ValueError("The method does not match")

    # Виконуємо першу ітерацію
    def calculateFirstIteration():
        iterator = numpy.empty([4, 5])
        for i in range(0, aMatrix.shape[0]): # Множимо кожен рядок на значення елементу Aii
            arr = numpy.array(-aMatrix[i] / aMatrix[i][i])
            arr[i] = 0
            arr = numpy.append(arr, bVector[i] / aMatrix[i][i])
            iterator[i] = arr
        return iterator

    # Виконуємо Xk ітерацію
    def calculatingXK(matrix, previousX):
        return matrix @ previousX

    iter = calculateFirstIteration()
    currentX = numpy.array([0,0,0,0])
    previousX = numpy.array([100,100,100,100])
    while numpy.abs(numpy.amax(currentX - previousX)) > eps: # Умова припинення процессу
        bufferX = calculatingXK(iter, numpy.append(currentX, 1)) # Ітеративно множимо матрицю доки найбільший елемент матриці не стане меншим за епсілон
        previousX = currentX
        currentX = bufferX
    return currentX

aMatrix = numpy.array([[5, -1, 1, -1], [-1, 15, -1, 1], [1, -1, 15, -1], [-1, 1, -1, 15]])
bVector = numpy.array([15, 5, -9, 15])

print("-----------Square Root Method-----------")
print("Roots:", squareRootMethod(aMatrix, bVector).astype(numpy.float32))

print("\n--------------Yakobi Method------------")
print("Roots:", yakobiMethod(aMatrix, bVector).astype(numpy.float32))

# Число обумовленості
inversedAMatrix = numpy.linalg.inv(aMatrix)
print("Number of conditionally is ", numpy.linalg.norm(aMatrix, numpy.inf) * numpy.linalg.norm(inversedAMatrix, numpy.inf))