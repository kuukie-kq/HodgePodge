import sys
from PyQt5.QtGui import QGuiApplication, QIcon
from PyQt5.QtCore import Qt, QUrl, QTimer
from PyQt5.QtWidgets import QApplication, QWidget, QSystemTrayIcon, QAction, QMenu
from PyQt5.QtWebEngineWidgets import QWebEngineView
import time
import threading
from system.server.proxy_html import run as server_run
from system.server.proxy_html import server_url

"""
纯净版
"""


class Live2DShadow(QWidget):
    def __init__(self, rect, parent=None):
        super(Live2DShadow, self).__init__(parent)
        # 定义变量
        self.q_rect = rect  # 桌面信息
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
        self.setWindowFlags(
            Qt.SubWindow | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)  # 子窗口（无任务栏），窗口总是处在最上层，无边框窗口
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
        self.q_sys_tray_icon.setIcon(QIcon("./static/img/icon.png"))  # 图标
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
        from system.server.proxy_html import server_url
        self.q_live_view.load(QUrl(server_url()))
        self.q_live_view.show()

    pass


class Live2D(QWidget):
    _live2d = None
    _flag = 11

    def __init__(self, rect, parent=None):
        super(Live2D, self).__init__(parent)
        # 定义变量
        self.q_rect = rect  # 桌面信息
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
        self.setWindowFlags(
            Qt.SubWindow | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)  # 子窗口（无任务栏），窗口总是处在最上层，无边框窗口
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
        self.q_sys_tray_icon.setIcon(QIcon("./static/img/icon.png"))  # 图标
        self.q_sys_tray_icon.setToolTip("Live2D")  # 信息
        self.q_sys_menu.addAction(self.q_sys_show_action)
        self.q_sys_menu.addAction(self.q_sys_exit_action)
        self.q_sys_menu.addAction(self.q_sys_shadow_action)
        self.q_sys_tray_icon.setContextMenu(self.q_sys_menu)  # 菜单
        self.q_sys_tray_icon.show()

    def _in_it_live_widget(self):
        # QWebEngineView默认元素大小100x30
        self.q_live_view.setGeometry(0, 0, self.q_rect.width(), self.q_rect.height())
        self.q_live_view.setAttribute(Qt.WA_TranslucentBackground, True)
        self.q_live_view.setStyleSheet("background: transparent;")
        self.q_live_view.page().setBackgroundColor(Qt.transparent)

    def _in_it_live_view(self):
        self.q_live_view.load(QUrl(server_url()))
        self.q_live_view.show()

    def on_exit_app_action(self):
        if Live2D._live2d is not None:
            Live2D._live2d.close()
            Live2D._live2d = None
        self.close()
        sys.exit()

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
    live2d.show()
    sys.exit(app.exec_())
