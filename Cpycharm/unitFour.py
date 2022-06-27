# 2
import numpy as np

arrOne = np.array([1, 12, 11, 17, 13, 18, 12, 14])
print(arrOne[arrOne % 2 == 0])
# print(arrOne[1, 5, 6, 7])
# 3
arrTwo = np.array([[1, 12, 11, 17], [13, 18, 12, 14], [8, 11, 14, 10], [6, 8, 19, 22]])
print(arrTwo[2, :])
print(arrTwo[:, 1])
# 4
sumRows = []
for i in range(arrTwo.shape[0]):
    sumRow = 0
    for j in range(arrTwo.shape[1]):
        sumRow = sumRow + arrTwo[i, j]
    sumRows.append(sumRow)
print(sumRows)
# 5
stuScore = np.genfromtxt(fname=r'D:\MyPFile\BigDataPythonFile\stu_score.txt',
                         delimiter='\t', skip_header=1)
print(np.mean(stuScore, axis=0))
# 6
print(np.dot(np.random.randint(0, 10, (5, 3)), np.random.randint(0, 10, (3, 2))))
# 7
print(arrTwo.reshape(8, 2))
# 8
print(np.vstack([np.arange(10).reshape(2, -1), np.repeat(1, 10).reshape(2, -1)]))
# 9
arrThree = np.array([1, 2, 3, 2, 3, 4, 3, 4, 5, 6])
# arrFour = []
# for i in arrThree:
#     if i not in arrFour:
#         arrFour.append(i)
# print(np.array(arrFour))
print(np.unique(arrThree))
# 10
for i in range(arrTwo.shape[0]):
    for j in range(arrTwo.shape[1]):
        if (arrTwo % 2 == 0)[i, j]:
            arrTwo[i, j] = -1
print(arrTwo)
# 11
from numpy.linalg import solve

print(solve(np.mat([[1, 1], [2, 3]]), np.mat([7, 18]).T))
# 12多元线性回归模型为：Y=b0+b1x1+...+bkxk+e
# 13
arrFour = np.random.randint(0, 50, 10)
print(arrFour)
maxNum = 0
for i in range(10):
    if arrFour[i] > maxNum:
        maxNum = arrFour[i]
        j = i
arrFour[j] = 0
print(arrFour)
# 14
money = 1000
result = np.random.rand(1000)
for i in range(1000):
    if result[i] < 0.5:
        money -= 8
    else:
        money += 8
print(money)
