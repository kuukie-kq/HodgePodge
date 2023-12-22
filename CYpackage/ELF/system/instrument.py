import sys
from PyQt5.QtGui import QGuiApplication, QIcon
from PyQt5.QtCore import Qt, QUrl, QTimer, QEventLoop, QFile, QTextStream
from PyQt5.QtWidgets import QApplication, QWidget, QSystemTrayIcon, QAction, QMenu
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWebChannel import QWebChannel
from system.proxy.protol_qtjs import Buffer, commend_start
from system.configuration.analysis import register
"""
首页
"""


class Control(QWidget):
    _address = "127.0.0.1:50024"

    def __init__(self):
        super(Control, self).__init__()
        self._q_web_view = QWebEngineView(parent=self)
        self._q_web_channel = QWebChannel(self._q_web_view.page())
        self._q_web_buffer = Buffer(self)
        # 初始化
        self._in_it_attribute()
        self._in_it_connect_func()

    def _in_it_attribute(self):
        self.setWindowTitle("Live2D-助手")
        # 固定窗口大小
        self.setMaximumSize(1280, 800)
        self.setMinimumSize(1280, 800)
        self.setWindowIcon(QIcon("./static/img/icon.ico"))
        # 界面采用html交互利用channel
        self._q_web_view.setGeometry(0, 0, 1280, 800)
        self._q_web_channel.registerObject("buffer", self._q_web_buffer)
        self._q_web_view.page().setWebChannel(self._q_web_channel)
        self._q_web_view.page().load(QUrl("http://{address}/welcome/instrument.html".format(address=Control._address)))
        self._q_web_view.show()

    def _in_it_connect_func(self):
        # 绑定各种触发事件（槽函数）
        self._q_web_buffer.requestFromMessage.connect(self._on_recv_js)
        # 默认为函数调用（阻塞模式）Qt.QueuedConnection为事件队列（非阻塞模式）注意为不同事件队列（好像是窗体）间，同一队列处理依然阻塞队列的处理
        self._q_web_buffer.requestFromCommend.connect(self.on_run_executable)

    def _on_recv_js(self, message):
        if message == "open_terminal":
            self.on_open_terminal()
        else:
            print(message)

    def on_open_terminal(self):
        self.__sizeof__()
        commend_start("wt")

    def on_run_executable(self, path):
        self.__sizeof__()
        if type(path) == str:
            commend_start(path)

    pass


def instrument_run(args=None):
    if args is not None:
        from system.configuration.conf_parameters import Config
        c = Config(args)
        if c.check != 1:
            sys.exit(1)
        Control._address = c.welcome_address()
        pass
    app = QApplication(sys.argv)
    control = Control()
    control.show()
    sys.exit(app.exec_())


register("inst", instrument_run, 2)
