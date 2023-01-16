import os
import sys
from PyQt5.QtGui import QIcon, QMovie
from PyQt5.QtCore import Qt, QSize, QTimer
from PyQt5.QtWidgets import QApplication, QWidget, QAction, QMenu, QLabel, QSystemTrayIcon

# 参考内容具体解释从网址中查看
# https://blog.csdn.net/zujiasheng/article/details/124670676


class Test(QWidget):
    """
    测试桌宠简单程序
    首先桌宠思路
    1.实现方式利用QT的窗口框架，将桌宠封装在QT中
    2.让QT渲染的窗口变成一个特殊的窗口
    3.内部简单方式通过加载gif，以及简单的QT控件交互
    设想的实现
    利用live2d技术让桌宠可以更加灵活的活动，来实现不同的效果动作
    后续功能添加
    日期，以及对应日期祝福等（参考html中live2d对话交互实现）
    检测鼠标位置，自动躲开鼠标
    作为命令接口，可以执行输入命令
    python做还是c++做，备忘录
    工作计划安排表
    """
    def __init__(self, parent=None, **kwargs):
        super(Test, self).__init__(parent)
        self.tray_icon = QSystemTrayIcon(self)
        self.tray_icon_menu = QMenu(self)
        self.talk_label = QLabel(self)
        self.live2d = QLabel(self)
        self.movie = QMovie("test.gif")
        self.timer = QTimer()
        self.init()
        self.init_base()
        self.init_pet()
        self.normal_action()

    def init(self):
        self.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.SubWindow)
        self.setAutoFillBackground(False)
        self.setAttribute(Qt.WA_TranslucentBackground, True)
        self.repaint()

    def init_base(self):
        icons = os.path.join("icon.png")
        quit_action = QAction("关闭", self)
        quit_action.setIcon(QIcon(icons))
        quit_action.triggered.connect(self.quit)
        self.tray_icon_menu.addAction(quit_action)
        self.tray_icon.setIcon(QIcon(icons))
        self.tray_icon.setContextMenu(self.tray_icon_menu)
        self.tray_icon.show()

    def init_pet(self):
        self.talk_label.setStyleSheet("border-width: 1px; color: red;")
        self.movie.setScaledSize(QSize(200, 200))
        self.live2d.setMovie(self.movie)
        self.movie.start()
        self.resize(1024, 1024)
        self.move(0, 0)
        self.show()

    def normal_action(self):
        # self.timer.timeout.connect()
        # self.timer.start()
        pass

    def quit(self):
        self.close()
        sys.exit()

    pass


def run():
    qt_app = QApplication(sys.argv)
    t = Test()
    sys.exit(qt_app.exec_())
