import pandas as pd

# 读取外卖平台的订单数据，表名为orders.xlsx
orders = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\orders.xlsx', skiprows=1)

# 对订单金额、支付金额做基本的统计描述，判断数据是否存在明显的偏态
import matplotlib.pyplot as plt

plt.style.use('ggplot')
orders.order_amt.plot(kind='hist', bins=30, density=True)
orders.order_amt.plot(kind='kde')
orders.pay_amt.plot(kind='hist', bins=30, density=True)
orders.pay_amt.plot(kind='kde')
plt.show()
# 由图可得不存在明显的偏态，基本符合正态分布

# 在原有表的基础上生成subsidy变量，用于存储每笔订单的补贴额
orders['subsidy'] = orders.order_amt - orders.pay_amt


# 将订单运送时长转换为分钟单位
def toMinute(time):
    if time >= 1000:
        time = (time % 100) / 60 + time / 100
    else:
        time = (time % 10) / 60 + time / 10
    return time


# 对订单运送时长做基本的统计描述
orders.send_time = orders.send_time.str[: 2] + orders.send_time.str[3: -1]
orders.send_time = orders.send_time.astype('int')
orders.send_time = orders.send_time.apply(func=lambda x: toMinute(x))

print(orders.describe(include=['float64']))

# 计算偏度和峰度
# def skew_kurt(x):
#     return pd.Series([x.skew(), x.kurt()], index=['skew', 'kurt'])
#
#
# orders.send_time.apply(func=skew_kurt)
# 筛选出补贴额在8元以上的订单
print(orders.loc[orders.subsidy >= 8])

# 将手机号中间四位隐藏起来
orders.tel = orders.tel.astype('str')
orders.tel = orders.tel.apply(func=lambda x: x.replace(x[3:7], 'kksk'))


# 统计午高峰和晚高峰的订单比例
def judgeWIIALON(time):
    time_hour = time.split(" ")[1].split(":")[0]
    if (time_hour == '10') | (time_hour == '11'):
        return 5
    elif (time_hour == '18') | (time_hour == '19') | (time_hour == '20'):
        return 9
    else:
        return 0


odt = orders.order_time.apply(func=lambda x: judgeWIIALON(x))
lunch = dinner = another = 0
for i in odt:
    if i == 5:
        lunch += 1
    elif i == 9:
        dinner += 1
    else:
        another += 1
print("午高峰的订单比例为", lunch * 100 / (lunch + dinner + another), "%")
print("晚高峰的订单比例为", dinner * 100 / (lunch + dinner + another), "%")


# 基于支付金额，将支付金额的前20%划分为A等级，接下来20%~50%划分为B等级，剩下的50%划分为C等级
orders['level'] = '0'
twenty = orders.pay_amt.quantile(q=0.2, interpolation='midpoint')
fifty = orders.pay_amt.quantile(q=0.5, interpolation='midpoint')
for i in range(len(orders)):
    if orders.pay_amt[i] < twenty:
        orders.level[i] = 'A'
    elif i < fifty:
        orders.level[i] = 'B'
    else:
        orders.level[i] = 'C'

# 按订单状态统计各状态下的平均订单金额
import numpy as np

grouped = orders.groupby(by='order_status')
result = grouped.aggregate({'order_amt': np.mean})
print(result)

print(orders.head(8))
