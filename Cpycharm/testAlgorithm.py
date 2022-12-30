from itertools import combinations, permutations
array = [1, 2, 3, 4, 5, 6, 7]


def on511step():
    one = combinations(array, 5)
    two = []
    res_msg = []
    for o in list(one):
        two.append(permutations(o))
    for t in list(two):
        for tw in t:
            first = 0
            three = [1, 2, 3, 4, 5, 6, 7]
            for i in tw:
                first = first * 10 + i
                three.remove(i)
            second = three[0]
            third = three[1]
            res_msg.append((str(first) + "+" + str(second) + "-" + str(third) + "=" + str(first + second - third), first + second - third))
            res_msg.append((str(first) + "+" + str(third) + "-" + str(second) + "=" + str(first + third - second), first + third - second))
            # res_msg.append((str(third) + "+" + str(second) + "-" + str(first) + "=" + str(third + second - first), third + second - first))
    return res_msg


if __name__ == "__main__":
    print("Hello World\n从1234567七个数中任意组合成3个数并依次做加和减运算，找到一个最接近目标值的组合算式\n主要是排列组合库的使用")
    goal = 61456
    print("goal:", goal)
    mn = 100000
    msg = ""
    res_msg_num = on511step()
    for m, n in res_msg_num:
        if goal > n:
            if (goal - n) < mn:
                mn = goal - n
                msg = m
        else:
            if (n - goal) < mn:
                mn = n - goal
                msg = m
    print(msg)
    pass
