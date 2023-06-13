from system.configure.analysis import Analysis

if __name__ == "__main__":
    print("Hello World")
    ana = Analysis()
    ana.tag_run()
    pass

# 使用说明
# diy自己的桌宠，设想能够做到全屏相对智能的交互，并具有类似备忘录任务表等附加功能
# ====  ==== ====  ==== ====  ==== ====  ==== ====  ==== ====  ==== ###
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
# ====  ==== 2023-01-19 通过浏览器发现live2d自带的拖拽功能，使用了JQuery等组
# ====  ==== ====  ==== 件，而其只能使用跨域请求才能完成初始化，从而无响应（跨
# ====  ==== ====  ==== 域问题）
# ====  ==== 2023-01-28 使用bottle框架，简单搭建了一个web服务，类似nginx将
# ====  ==== ====  ==== live2d资源进行管理，同样碰到了跨域问题，虽然从结果上解
# ====  ==== ====  ==== 决了跨域问题，但并不是代码中解决的（有点混乱，需要后续验
# ====  ==== ====  ==== 证）同时碰到了新的问题，python线程相关（考虑换成协程）
# ====  ==== ====  ==== 且碰到了路径问题，原本的nohup方式运行不再适用
# ====  ==== 2023-01-31 重新写了一个pure2d，表示纯净版的live2d并尝试将程序进
# ====  ==== ====  ==== 行打包（使用pyinstaller）主要问题为需要手动拷贝QT相关
# ====  ==== ====  ==== 库文件（dll，exe），版本为0.0.1.31
# ====  ==== 2023-02-03 尝试通过javascript注入的方式获取一些需要的交互信息，并
# ====  ==== ====  ==== 进行打包（使用pyinstaller）确定为1.0.2.3
# ====  ==== 2023-02-06 还存在的一些问题，快捷键的响应，live2d资源部分的加载问
# ====  ==== ====  ==== 题（有跨域，也有签证等）考虑变成本地资源
# ====  ==== 2023-02-10 发现快捷键绑定与其作用域相关，比如其作为最外层窗口上，当
# ====  ==== ====  ==== 该窗口hide后依然无法响应快捷键（既测试绑定的同一个快捷
# ====  ==== ====  ==== 键可以连续按三次形成循环，但是shadow窗口是因为鼠标穿透，
# ====  ==== ====  ==== 如果点了一下失去焦点，则快捷键依然不起作用）
# ====  ==== 2023-02-16 增加了子函数参数校验，目的为配置文件做准备
# ====  ==== 2023-02-17 通过打包后一些场景测试发现，live2d所使用的后端资源（骨
# ====  ==== ====  ==== 架，动作，材质等）由于各种原因而出现请求失败问题，于是将
# ====  ==== ====  ==== 这些也一并进行本地化（也是对bottle框架进一步学习）目前
# ====  ==== ====  ==== 仅实现基本功能，既资源的请求，换装等还未补充
# ====  ==== 2023-02-21 基本完成了整个需要用到的请求，并打包1.2.0后续研究一下动
# ====  ==== ====  ==== 作触发等问题，看怎么样在无鼠标键盘事件情况下实现一些交互
# ====  ==== ====  ==== 同时也将配置文件的解析等补充
# ====  ==== 2023-04-28 模块优化封装预计，map自动生成映射关系，封装logger信息
# ====  ==== ====  ==== ，基本上重构（private以_开头），一些临时的引用使用局部
# ====  ==== ====  ==== from-import
# ====  ==== 2023-06-12 map采用注册的形式动态（解析时）加载，存在循环引用问题以
# ====  ==== ====  ==== 及unused警告，重构（主要部分不含-，private含-临时引
# ====  ==== ====  ==== 用），未加log&conf&welcome page&game
