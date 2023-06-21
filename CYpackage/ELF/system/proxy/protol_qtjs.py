import os
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot


class Buffer(QObject):
    # 信号量-rpc接口
    def __init__(self, parent=None):
        super(Buffer, self).__init__(parent)

    # buffer->qt信号  connect在qt
    requestFromMessage = pyqtSignal(str)
    requestFromCommend = pyqtSignal(str)
    # qt->web信号  connect在web

    # web->buffer  无需connect  call即可
    @pyqtSlot(str)
    def no_parameter_call(self, s):
        self.requestFromMessage.emit(s)

    @pyqtSlot(str)
    def str_commend_call(self, s):
        self.requestFromCommend.emit(s)

    pass


def commend_start(commend):
    # 一般写法
    # with os.popen(commend) as p:
    #     pass
    # 非阻塞写法  为何不许手动close
    os.popen(commend)
