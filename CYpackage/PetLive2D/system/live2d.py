import sys
import warnings
from PyQt5.QtGui import QGuiApplication, QIcon
from PyQt5.QtCore import Qt, QUrl, QTimer
from PyQt5.QtWidgets import QApplication, QWidget, QSystemTrayIcon, QAction, QMenu
from PyQt5.QtWebEngineWidgets import QWebEngineView
import time
import ctypes
import inspect
import threading
from system.server.botstat import run as server_run


class Live2DShadow(QWidget):
    """
    live2d的影子
    既Live2D._live2d该实例的声明定义，也是Live2D最初的主要内容
    目的用于对窗体设置了鼠标穿透后，无法再次开启鼠标监听事件，固尝试影子的方式获取一些事件信息
    """
    def __init__(self, rect, parent=None):
        super(Live2DShadow, self).__init__(parent)
        # 定义变量
        self.q_rect = rect  # 桌面信息====无需保存
        self.q_sys_tray_icon = QSystemTrayIcon()  # 状态栏图标
        self.q_sys_show_action = QAction("显示", self)
        self.q_sys_hide_action = QAction("隐藏", self)
        self.q_sys_menu = QMenu(self)  # 状态栏图标的右键菜单
        self.q_live_view = QWebEngineView(parent=self)  # live2d的主元素
        # 自身设置
        self.setGeometry(0, 0, self.q_rect.width(), self.q_rect.height())
        self.setAutoFillBackground(False)  # 自动填充背景 false为透明背景
        self.setAttribute(Qt.WA_TranslucentBackground, True)  # 元素透明元素空间不透明
        # self.setAttribute(Qt.WA_TransparentForMouseEvents, True)  # 鼠标穿透
        self.setWindowFlags(Qt.SubWindow | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)  # 子窗口（无任务栏），窗口总是处在最上层，无边框窗口
        # 初始化
        self._in_it_connect_func()
        self._in_it_sys_task()
        self._in_it_live_widget()
        self._in_it_live_view()

    def _in_it_connect_func(self):
        # 绑定各种触发事件（槽函数）
        self.q_sys_show_action.triggered.connect(lambda: self.show())
        self.q_sys_hide_action.triggered.connect(lambda: self.hide())

    def _in_it_sys_task(self):
        # 状态栏相关设置
        self.q_sys_tray_icon.setIcon(QIcon("icon.png"))  # 图标
        self.q_sys_tray_icon.setToolTip("Live2DShadow")  # 信息
        self.q_sys_menu.addAction(self.q_sys_show_action)
        self.q_sys_menu.addAction(self.q_sys_hide_action)
        self.q_sys_tray_icon.setContextMenu(self.q_sys_menu)  # 菜单
        self.q_sys_tray_icon.show()

    def _in_it_live_widget(self):
        # QWebEngineView默认元素大小100x30
        self.q_live_view.setGeometry(0, 0, self.q_rect.width(), self.q_rect.height())
        self.q_live_view.setAttribute(Qt.WA_TranslucentBackground, True)
        self.q_live_view.setStyleSheet("background: transparent;")
        self.q_live_view.page().setBackgroundColor(Qt.transparent)

    def _in_it_live_view(self):
        from system.server.botstat import server_url
        self.q_live_view.load(QUrl(server_url()))
        self.q_live_view.show()

    pass


class Live2D(QWidget):
    """
    live2d的具体内容
    目前实现了live2d完全浮于桌面且不会抢其他窗口的鼠标键盘事件
    live2d部分发现直接使用本地资源存在跨域问题，考虑拉起一个web服务
    """
    _live2d = None
    _flag = 11  # 主要用于记录显示状态（将显示和隐藏按钮合成一个）10以下表示影子模式，11显示，12隐藏

    def __init__(self, rect, parent=None):
        super(Live2D, self).__init__(parent)
        # 定义变量
        self.q_rect = rect  # 桌面信息====无需保存
        self.q_sys_tray_icon = QSystemTrayIcon()  # 状态栏图标
        self.q_sys_show_action = QAction("显示/隐藏", self)
        self.q_sys_exit_action = QAction("关闭", self)
        self.q_sys_shadow_action = QAction("Shadow", self)
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
        self._in_it_live_view()
        # 其他 web服务 使用bottle框架 使用线程库 启动web服务
        self._thread = threading.Thread(target=server_run)
        self._thread.setDaemon(True)  # web服务 虽然不属于守护线程，但退出时可以忽略
        self._thread.start()
        time.sleep(2)

    def _in_it_connect_func(self):
        # 绑定各种触发事件（槽函数）
        self.q_sys_show_action.triggered.connect(self.on_show_or_hide_action)
        self.q_sys_exit_action.triggered.connect(self.on_exit_app_action)
        self.q_sys_shadow_action.triggered.connect(self.on_shadow_app_action)

    def _in_it_sys_task(self):
        # 状态栏相关设置
        self.q_sys_tray_icon.setIcon(QIcon("icon.png"))  # 图标
        self.q_sys_tray_icon.setToolTip("Live2D")  # 信息
        self.q_sys_menu.addAction(self.q_sys_show_action)
        self.q_sys_menu.addAction(self.q_sys_exit_action)
        self.q_sys_menu.addAction(self.q_sys_shadow_action)
        self.q_sys_tray_icon.setContextMenu(self.q_sys_menu)  # 菜单
        self.q_sys_tray_icon.show()

    def on_exit_app_action(self):
        # 强杀线程的方式，有问题，如果线程被阻塞（处于python之外）不会捕获到结束信号
        def _async_raise(tid, exit_type):
            warnings.warn("_async_raise function is deprecated (daemon or coroutine)", DeprecationWarning)
            tid = ctypes.c_long(tid)
            if not inspect.isclass(exit_type):
                exit_type = type(exit_type)
            res = ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, ctypes.py_object(exit_type))
            if 0 == res:
                raise ValueError("invalid thread id")
            else:
                ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, None)
                raise SystemError("PyThreadState_SetAsyncExc failed")
            pass
        # _async_raise(self._thread.ident, SystemExit)
        self.close()
        sys.exit()

    def _in_it_live_widget(self):
        # QWebEngineView默认元素大小100x30
        self.set_desktop(100, 100)
        self.q_live_view.setAttribute(Qt.WA_TranslucentBackground, True)
        self.q_live_view.setStyleSheet("background: transparent;")
        self.q_live_view.page().setBackgroundColor(Qt.transparent)

    def in_it_live_view(self, url):
        warnings.warn("in_it_live_view function is deprecated (url use network data)", DeprecationWarning)
        # 由于url的相对路径，其相对的基路径（可能是根或者空）未弄清楚，需要确认live2d资源路径能够正确调用
        print(QUrl().resolved(QUrl(url)).toString())
        self.q_live_view.page().load(QUrl(url))
        self.q_live_view.show()

    def _in_it_live_view(self):
        from system.server.botstat import server_url
        self.q_live_view.load(QUrl(server_url()))
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
        width = int((self.q_rect.width() - 300) * width_proportion / 100)
        height = int((self.q_rect.height() - 300) * height_proportion / 100)
        self.q_live_view.setGeometry(width, height, 300, 300)
        # self.q_live_view.setGeometry(0, 0, self.q_rect.width(), self.q_rect.height())

    def on_show_or_hide_action(self):
        if 11 == Live2D._flag:
            self.hide()
            Live2D._flag = 12
        elif 12 == Live2D._flag:
            self.show()
            Live2D._flag = 11
        else:
            pass

    def on_shadow_app_action(self):
        if Live2D._live2d is None:
            self.hide()
            Live2D._flag = 2
            Live2D._live2d = Live2DShadow(rect=self.q_rect)
            Live2D._live2d.setAttribute(Qt.WA_DeleteOnClose, True)  # 该窗口关闭时自动销毁该对象
            Live2D._live2d.show()
        else:
            Live2D._live2d.close()
            Live2D._live2d = None
            self.show()
            Live2D._flag = 11

    pass


def run():
    app = QApplication(sys.argv)
    rect = QGuiApplication.primaryScreen().availableGeometry()
    live2d = Live2D(rect=rect)
    # live2d.in_it_live_view(app.applicationDirPath() + "/../../../PycharmProjects/PetLive2D/static/free/live/demo.html")
    live2d.show()
    sys.exit(app.exec_())
