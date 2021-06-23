import matplotlib.pyplot as plt

# 1
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
price = [300, 120, 470, 200]
labels = ['张三', '李四', '王二', '赵五']

plt.figure(figsize=(14, 18))
ax1 = plt.subplot2grid(shape=(3, 2), loc=(0, 0))
ax2 = plt.subplot2grid(shape=(3, 2), loc=(0, 1))
ax3 = plt.subplot2grid(shape=(3, 2), loc=(1, 0))
ax5 = plt.subplot2grid(shape=(3, 2), loc=(2, 0))
ax6 = plt.subplot2grid(shape=(3, 2), loc=(2, 1))
ax4 = plt.subplot2grid(shape=(3, 2), loc=(1, 1))

explode = [0, 0, 0.1, 0]
ax1.pie(x=price, labels=labels, explode=explode, autopct='%.0f%%',
        wedgeprops={'linewidth': 1.5, 'edgecolor': 'green'},
        textprops={'fontsize': 10, 'color': 'blue'})
ax1.set_title('某销售小组的销售业绩-饼图')

ax2.bar(x=range(len(labels)), height=price, tick_label=labels)
x = 0
for y in price:
    ax2.text(x, y + 10, y, ha='center')
    x += 1
ax2.set_ylabel('销售额（万）')
ax2.set_title('某销售小组的销售业绩-条形图')

# 2
import pandas as pd

plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
pri = [12000, 8500, 6300, 8000, 5500, 6000, 10000, 4200, 6000, 8500,
       7600, 5400, 8800, 12800, 4200, 20000, 13200, 5000, 2500, 4200,
       13500, 2800, 11300, 8200, 4600, 7200, 4000, 5500, 4800, 11000,
       3800, 5200, 4700, 8800, 4500, 6800, 3000, 4500, 6500, 5500,
       3800, 4900, 5300, 5000, 4600, 5300, 4600, 5000, 23000, 10000]

prices = pd.Series(pri)
ax3.set_title('直方图和核密度曲线')
prices.plot(kind='hist', bins=20, density=True, ax=ax3)
prices.plot(kind='kde', ax=ax3)


# 3
def toFloat(num):
    n = num.split(" ")
    if len(n) == 2:
        return n[0] + n[1]
    elif len(n) == 1:
        return n[0]


shGDP = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\SH_GDP.xlsx',
                      # thousands=" ",
                      header=None, names=['Year', 'GDP', 'First', 'Second', 'Third', 'IE', 'CI'],
                      skiprows=1)
shGDP.GDP = shGDP.GDP.apply(lambda n: toFloat(n))
shGDP.GDP = shGDP.GDP.astype('float64')
shGDP.plot(kind='line', x='Year', y='GDP', ax=ax5)
ax5.set_title('GDP折线图')

shGDP.First = shGDP.First.apply(lambda n: toFloat(n))
shGDP.First = shGDP.First.astype('float64')
shGDP.Second = shGDP.Second.apply(lambda n: toFloat(n))
shGDP.Second = shGDP.Second.astype('float64')
shGDP.Third = shGDP.Third.apply(lambda n: toFloat(n))
shGDP.Third = shGDP.Third.astype('float64')
shGDP.plot(kind='line', x='Year', y=['First', 'Second', 'Third'], ax=ax6)
ax6.set_title('第一、二、三产业的折线图')

# 4
import seaborn as sns
import statsmodels.api as sm

sales = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\marketing.xlsx',
                      header=None, names=['One', 'Two', 'Three'],
                      skiprows=1)
sales.plot(kind='scatter', x='One', y='Two', ax=ax4)
sns.lmplot(x='One', y='Two', data=sales, ci=None)
fit = sm.formula.ols('Three ~ One + Two', data=sales).fit()
print(fit.params)

ax4.set_title('散点图')

import numpy as np
import random


def randomColor():
    colArr = ['1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    color = ""
    for i in range(6):
        color += colArr[random.randint(0, 14)]
    return "#" + color


colors = sales.Three.apply(lambda s: randomColor())
# colors = np.random.rand(len(sales))   随机生成[0,1)数
size = sales.Three.apply(lambda s: (s * 100) * (s * 100))
sales.plot(kind='scatter', x='One', y='Three', s=size, c=colors, ax=ax4)
ax4.set_title('散点图-气泡图')

plt.subplots_adjust(hspace=0.6, wspace=0.3)
plt.show()
