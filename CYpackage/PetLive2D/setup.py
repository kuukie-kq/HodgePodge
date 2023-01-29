from configure.analysis import Analysis

if __name__ == "__main__":
    print("Hello World")
    Analysis()
    pass

# 使用说明
# diy自己的桌宠，设想能够做到全屏相对智能的交互，并具有类似备忘录任务表等附加功能
# 编写日志：
# ====  ==== 2023-01-11 实际上想法很早就有了，不过最近发现存在实现的可能
# ====  ==== 2023-01-12 之前也了解到了实现原理，本质还是一个窗口，但是比较特殊
# ====  ==== ====  ==== 处于最底层或最上层，理论上动作的流畅度等需要live2d实现
# ====  ==== ====  ==== 这一部分的资源非常欠缺，并且可能需要自己封装live2d相关
# ====  ==== 2023-01-13 利用PyQtWebEngine模块，直接通过html解析的方式加载
# ====  ==== ====  ==== live2d到对应的组件元素块中，相当于python写了一个浏览
# ====  ==== ====  ==== 器（虽然是调库实现的）然后live2d部分则在浏览器上显示
# ====  ==== 2023-01-16 增加了启动参数的配置解析以及相关帮助说明，其中pass与
# ====  ==== ====  ==== python中的关键字pass一致，表示占位，从而保证了启动参
# ====  ==== ====  ==== 数的奇偶性，不过也有缺点，如果是数组参数的情况，需要多
# ====  ==== ====  ==== 次重复的冗余才能完成，不过启动的配置参数用不了那么多
# ====  ==== 2023-01-18 基本完成了桌宠的首要功能，作为一个特殊窗口浮与最上层，
# ====  ==== ====  ==== 且能够做到鼠标键盘事件穿透，不影响其他窗口的正常焦点捕
# ====  ==== ====  ==== 获等任务。并且尝试通过一些方式来让桌宠在这个前提下还能
# ====  ==== ====  ==== 特定的响应一些事件，目前并未找到合适的方式