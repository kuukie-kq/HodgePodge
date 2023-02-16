import sys
from PyQt5.QtGui import QGuiApplication, QIcon
from PyQt5.QtCore import Qt, QUrl
from PyQt5.QtWidgets import QApplication, QWidget, QSystemTrayIcon, QAction, QMenu
from PyQt5.QtWebEngineWidgets import QWebEngineView


class Live2DWidget(QWidget):
    """
    测试Qt对live2d的支持
    思路：
    live2d是基于html+js+json+资源的方式实现平面动作的，参考如下实现
    【C++Qt实现Live2D桌面萌宠】 https://www.bilibili.com/video/BV1q7411C79N/
    发现，无需自己做各种组件拼装等工作，直接引用web组件即可
    """
    def __init__(self, parent=None, rect=None):
        super(Live2DWidget, self).__init__(parent)
        # 自身设置
        self.setAutoFillBackground(False)
        self.setAttribute(Qt.WA_TranslucentBackground, True)
        self.setWindowFlags(Qt.SubWindow | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)
        # 定义变量
        self.q_rect = rect
        self.qSysTrayIcon = QSystemTrayIcon()
        self.qSysShowAction = QAction("显示", self)
        self.qSysExitAction = QAction("关闭", self)
        self.qSysHideAction = QAction("隐藏", self)
        self.qSysMoveTestAction = QAction("移动", self)
        self.qSysMenu = QMenu(self)
        self.qLiveView = QWebEngineView(parent=self)
        # 初始化
        self._in_it_connect_func()
        self._in_it_sys_task()
        self._in_it_live_widget()

    def _in_it_live_widget(self):
        # QWebEngineView默认元素大小100x30
        self.qLiveView.resize(300, 300)
        self.qLiveView.setAttribute(Qt.WA_TranslucentBackground, True)
        self.qLiveView.setStyleSheet("background: transparent;")
        self.qLiveView.page().setBackgroundColor(Qt.transparent)

    def in_it_live_view(self, url):
        # 由于url的相对路径，其相对的基路径（可能是根或者空）未弄清楚，需要确认live2d资源路径能够正确调用
        # print(QUrl().resolved(QUrl("static/free/live/demo.html")).toString())
        self.qLiveView.page().load(QUrl(url))
        self.qLiveView.show()

    def _in_it_connect_func(self):
        self.qSysTrayIcon.messageClicked.connect(self.on_show_main_action)
        self.qSysShowAction.triggered.connect(self.on_show_main_action)
        self.qSysExitAction.triggered.connect(self.on_exit_app_action)
        self.qSysHideAction.triggered.connect(lambda: self.hide())
        self.qSysMoveTestAction.triggered.connect(lambda: self.set_desktop(90, 90))

    def _in_it_sys_task(self):
        self.qSysTrayIcon.setIcon(QIcon("./static/img/icon.png"))
        self.qSysTrayIcon.setToolTip("Live2D")
        self.qSysMenu.addAction(self.qSysShowAction)
        self.qSysMenu.addAction(self.qSysExitAction)
        self.qSysMenu.addAction(self.qSysHideAction)
        self.qSysMenu.addAction(self.qSysMoveTestAction)
        self.qSysTrayIcon.setContextMenu(self.qSysMenu)
        self.qSysTrayIcon.show()

    def on_show_main_action(self):
        self.show()

    def on_exit_app_action(self):
        self.close()
        sys.exit()

    def set_desktop(self, width_proportion=100, height_proportion=100):
        if width_proportion > 100:
            width_proportion = 100
        elif width_proportion < 0:
            width_proportion = 0
        if height_proportion > 100:
            height_proportion = 100
        elif height_proportion < 0:
            height_proportion = 0
        width = (self.q_rect.width() - 300) * width_proportion / 100
        height = (self.q_rect.height() - 300) * height_proportion / 100
        self.setGeometry(width, height, 300, 300)

    pass


def run(args=None):
    qt_app = QApplication(sys.argv)
    screen = QGuiApplication.primaryScreen()
    rect = screen.availableGeometry()
    live2d = Live2DWidget(rect=rect)
    live2d.in_it_live_view(qt_app.applicationDirPath() + "/../../../PycharmProjects/PetLive2D/static/free/Live2D/demo.html")
    live2d.set_desktop(10, 90)
    live2d.on_show_main_action()
    sys.exit(qt_app.exec_())
