import sys
import datetime
from system.test_first import run as test1run
from system.test_second import run as test2run
from system.live2d import run as live2d_main_run
from system.pure2d import run as pure_live2d_run


class Analysis:
    """
    分析
    目前主要用作参数配置分析，来调用对应的效果
    """
    # 静态变量
    _version_main = 1
    _version_sub = 2
    _version_stage = 0
    _version_other = 3220

    def __init__(self):
        self._arg_size = sys.argv.__len__()
        self._arg_array = sys.argv
        self.tag_func = lambda x: print("テスト関数")
        self.tag_index = 0
        self.tag_argv = []
        self.tgl_func = {"test1": test1run, "test2": test2run, "live2d": live2d_main_run, "pl2d": pure_live2d_run}
        self.tgl_max = {pure_live2d_run: 4}
        self.check = self._check_args()

    def _check_args(self):
        self.tag_argv = []
        self.tag_index = 0
        if self._arg_size == 1:
            # 默认情况
            self.tag_func = pure_live2d_run
        else:
            if self._arg_size % 2 == 1:
                for i in range(1, self._arg_size, 2):
                    arg_key = self._arg_array[i]
                    arg_value = self._arg_array[i + 1]
                    arg_flag = self._args_analysis(arg_key, arg_value)
                    if arg_flag == 2:
                        return 0
                    elif arg_flag == 0:
                        break
            else:
                self._error_information("参数格式异常，参考-help信息")
                self._help_information()
                return 0
        return 1

    def _warning_information(self, message):
        print("<-->" + datetime.datetime.now().strftime("%Y-%m-%d") + message)
        self.__sizeof__()

    def _error_information(self, message):
        print("<**>" + datetime.datetime.now().strftime("%Y-%m-%d") + message)
        print("==== args:" + str(self._arg_size))

    def _args_analysis(self, key, value):
        """0:break 1:continue 2:exit"""
        if "-version" == key:
            if "pass" != value:
                self._warning_information("-version参数异常key:-version value:" + value)
            self._version_information()
            return 2
        elif "-help" == key:
            if "pass" != value:
                self._warning_information("-help参数异常key:-help value:" + value)
            self._help_information()
            return 2
        elif "-exec" == key:
            if "pass" == value:
                return 0
            # self.tag_func = self.tgl_func.get(value, default=lambda: print("テスト関数"))
            self.tag_func = self.tgl_func.get(value, lambda x: print("テスト関数"))  # 语法没问题但由于python底层c对default无法解析参数名称导致
            return 1
        elif "-argv" == key:
            if "pass" == value:
                self._error_information("-argv参数错误 key:-argv value:pass")
                return 2
            self.tag_index = self.tag_index + 1
            self.tag_argv.append(value)
            return 1
        else:
            self._error_information("未知参数错误 [key:" + key + "][value:" + value + "]")
            return 2
        pass

    def _version_information(self):
        version = str(self._version_main) + "." + str(self._version_sub) + "." + str(self._version_stage)
        print("version " + version + " PetLive2D.setup(Analysis)")

    def _help_information(self):
        print()
        print("Copyright python 3.8 anaconda3-2022-05 standard module")
        print("==== ==== pip install ---- pyqt5 (PyQtWebEngine)")
        print("==== ==== Create by kuu-kie <3260681415@qq.com> on 20230101")
        print("%d.%d.%d.%d" % (self._version_main, self._version_sub, self._version_stage, self._version_other))
        print("Usage: python setup.py [<key> <value>] ...")
        print("==== ====                 key-value help")
        print("-version pass           : display version and exit")
        print("-help pass              : display help and exit")
        print("-exec [pass | <name>]   : use name pet mode and last show")
        print("-argv <args>            : set custom function arguments (str) one by one")
        print("ps   : pass is placeholder keyword which used in key-non-value and weak check")
        print("p*ps : ... 为前面的内容可重复")
        print("       <> 为占位参数，里面的内容具有一定的含义")
        print("       [] 为可选参数")
        print("       () 为必选组合")
        print("       | 表示互斥关系只能使用其一")
        print("       pass 为弱占位符，最好不要有其他含义")
        print()
        print("-exec names", self.tgl_func.keys())
        print("ありがとうございました，またねー")

    def tag_run(self):
        if self.check == 1:
            if self.tag_index == 0:
                self.tag_func(None)
            elif self.tgl_max.get(self.tag_func, 0) >= self.tag_index:
                self.tag_func(self.tag_argv)
            else:
                print("<**>" + datetime.datetime.now().strftime("%Y-%m-%d") + "= The function is not open, please look forward to it")
                print("==== func:" + self.tag_func.__str__() + " args:" + str(self.tag_index))
        pass

    pass
