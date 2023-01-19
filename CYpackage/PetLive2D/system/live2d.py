import sys
from PyQt5.QtGui import QGuiApplication, QIcon
from PyQt5.QtCore import Qt, QUrl, QTimer
from PyQt5.QtWidgets import QApplication, QWidget, QSystemTrayIcon, QAction, QMenu
from PyQt5.QtWebEngineWidgets import QWebEngineView


class Live2D(QWidget):
    """
    live2d的具体内容
    目前实现了live2d完全浮于桌面且不会抢其他窗口的鼠标键盘事件
    """
    def __init__(self, rect, parent=None):
        super(Live2D, self).__init__(parent)
        # 定义变量
        self.q_rect = rect  # 桌面信息====无需保存
        self.q_sys_tray_icon = QSystemTrayIcon()  # 状态栏图标
        self.q_sys_show_action = QAction("显示", self)
        self.q_sys_exit_action = QAction("关闭", self)
        self.q_sys_hide_action = QAction("隐藏", self)
        self.q_sys_menu = QMenu(self)  # 状态栏图标的右键菜单
        self.q_live_view = QWebEngineView(parent=self)  # live2d的主元素
        self.timer = QTimer()
        # 自身设置
        self.setGeometry(0, 0, self.q_rect.width(), self.q_rect.height())
        self.setAutoFillBackground(False)  # 自动填充背景 false为透明背景
        self.setAttribute(Qt.WA_TranslucentBackground, True)  # 元素透明元素空间不透明
        self.setAttribute(Qt.WA_TransparentForMouseEvents, True)  # 鼠标穿透
        self.setWindowFlags(Qt.SubWindow | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)  # 子窗口（无任务栏），窗口总是处在最上层，无边框窗口
        # 初始化
        self._in_it_connect_func()
        self._in_it_sys_task()
        self._in_it_live_widget()

    def _in_it_connect_func(self):
        # 绑定各种触发事件（槽函数）
        self.q_sys_show_action.triggered.connect(lambda: self.show())
        self.q_sys_exit_action.triggered.connect(self.on_exit_app_action)
        self.q_sys_hide_action.triggered.connect(lambda: self.hide())

    def _in_it_sys_task(self):
        # 状态栏相关设置
        self.q_sys_tray_icon.setIcon(QIcon("icon.png"))  # 图标
        self.q_sys_tray_icon.setToolTip("Live2D")  # 信息
        self.q_sys_menu.addAction(self.q_sys_show_action)
        self.q_sys_menu.addAction(self.q_sys_hide_action)
        self.q_sys_menu.addAction(self.q_sys_exit_action)
        self.q_sys_tray_icon.setContextMenu(self.q_sys_menu)  # 菜单
        self.q_sys_tray_icon.show()

    def on_exit_app_action(self):
        self.close()
        sys.exit()

    def _in_it_live_widget(self):
        # QWebEngineView默认元素大小100x30
        self.set_desktop(95, 95)
        self.q_live_view.setAttribute(Qt.WA_TranslucentBackground, True)
        self.q_live_view.setStyleSheet("background: transparent;")
        self.q_live_view.page().setBackgroundColor(Qt.transparent)

    def in_it_live_view(self, url):
        # 由于url的相对路径，其相对的基路径（可能是根或者空）未弄清楚，需要确认live2d资源路径能够正确调用
        # print(QUrl().resolved(QUrl("static/free/live/demo.html")).toString())
        self.q_live_view.page().load(QUrl(url))
        self.q_live_view.show()

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
        self.q_live_view.setGeometry(width, height, 300, 300)

    pass


def run():
    app = QApplication(sys.argv)
    rect = QGuiApplication.primaryScreen().availableGeometry()
    live2d = Live2D(rect=rect)
    live2d.in_it_live_view(app.applicationDirPath() + "/../../../PycharmProjects/PetLive2D/static/free/live/demo.html")
    live2d.show()
    sys.exit(app.exec_())
