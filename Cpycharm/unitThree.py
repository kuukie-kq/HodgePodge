# 1 导入re模块
from typing import re

listOne = [1, 1, 2, 3, 5, 8, 13]
listOne.append(21)
print(listOne)
# 2
listTwo = ['语文', '数学', '英语', '物理']
listTwo.extend(['化学', '美术'])
print(listTwo)
# 4
dictFour = {'name': 'Lucy', 'age': 27, 'gender': 'female'}
print(dictFour['age'])
print(dictFour.get('age'))
# 5
# dictFour.update({'income': '10000'})
# dictFour.setdefault('income', '10000')
dictFour['income'] = 10000
print(dictFour.items())
# 6
import re

stringOne = "18.69元/500g"
print(re.findall('(.*?)元', stringOne))
# 7
stringID = '123456199001107890'
print(stringID[-2])
# 8
print(stringID[6:14])
# 9
numOne = 23
if int(numOne) % 3 == 0:
    print("相关")
else:
    while True:
        if int(numOne) % 10 == 3:
            print("相关")
            break
        else:
            if int(numOne) > 0:
                numOne = int(numOne) / 10
            else:
                print("不相关")
                break
# 10
listThree = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
for i in listThree:
    if i.find('e') >= 0:
        print(i)


# 11
def testEleven(number):
    result = 2 ** (number - 1) * 3
    return result


print(testEleven(6))
# 12
listFour = ['A', 'A', 'B', 'A', 'C', 'A', 'B', 'A', 'C', 'B', 'C', 'A', 'C']
dictTwo = {}
for i in listFour:
    dictTwo.setdefault(i, listFour.count(i))
print(dictTwo.items())
# 13
for i in range(0, 5):
    stringName = input("请输入用户名:")
    stringPassward = input("请输入密码:")
    if (stringName == "python") & (stringPassward == "abc123"):
        print("Welcome!")
        break
    else:
        if 5 - i == 1:
            print("用户名或密码错误,请24小时后重试")
            break
        else:
            print("用户名或密码错误,您还剩", 5 - i - 1, "次机会")
# 14
listFive = ['1室1厅 | 44.39平方米 | 南 | 简装 - 高楼层（共6层） | 1996年建',
            '1室0厅 | 29.39平方米 | 北 - 精装修 | 低楼层（共5层） | 1957年建',
            '2室1厅 | 56.65平方米 | 南 | 简装 - 高楼层（共6层） | 1995年建',
            '3室2厅 | 118.41平方米 | 南 - 精装 - 低楼层（共39层）']
listSize = []
listYear = []
for i in listFive:
    if len(re.split("[|-]", i)) == 6:
        listSize.append(re.split("[|-]", i)[1].strip())
        listYear.append(re.split("[|-]", i)[5].strip())
    elif len(re.split("[|-]", i)) == 5:
        listSize.append(re.split("[|-]", i)[1].strip())
        listYear.append('')
    else:
        pass
print(listSize, listYear)
