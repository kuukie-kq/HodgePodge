from system.service.sys_format_tool import op_print as hint


class Analysis:
    # 静态变量
    _version_main = 1
    _version_sub = 2
    _version_stage = 8
    _version_other = 4306
    #
    tgl_func = {}
    tgl_max = {}

    def __init__(self, length=1, value=None):
        # 系统参数
        self._arg_size = length
        self._arg_array = value
        #
        self._tag_func = lambda x: print("テスト関数")
        self._tag_index = 0
        self._tag_argv = []
        self._check = 0

    def _args_analysis(self, key, value):
        """0:break 1:continue 2:exit"""
        if "-version" == key:
            if "pass" != value:
                pass
            self._version_information()
            return 2
        elif "-help" == key:
            if "pass" != value:
                pass
            self._help_information()
            return 2
        elif "-exec" == key:
            if "pass" == value:
                return 0
            # self.tag_func = Analysis.tgl_func.get(value, default=lambda: print("テスト関数"))
            self._tag_func = Analysis.tgl_func.get(value, lambda x: print("テスト関数"))  # 语法没问题但由于python底层c对default无法解析参数名称导致
            return 1
        elif "-argv" == key:
            if "pass" == value:
                return 2
            args = value.split(",")
            self._tag_index = self._tag_index + args.__len__()
            self._tag_argv = self._tag_argv + args
            return 1
        else:
            hint("err", "key:%s,value:%s,unknow key" % (key, value))
            return 2
        pass

    def _check_args(self):
        self._tag_argv = []
        self._tag_index = 0
        if self._arg_size == 1:
            self._default_analysis()
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
                return 2
        return 1

    def argument_set(self):
        if self._check_args() != 1:
            pass

    def config_set(self):
        from system.argument.default import ArgD
        from system.argument.situation import Args
        Args.set_version_main(ArgD.get_version_main())
        Args.set_version_sub(ArgD.get_version_sub())
        Args.set_version_stage(ArgD.get_version_stage())
        Args.set_config_file_path(ArgD.get_config_file_path())
        Args.set_front_html_host(ArgD.get_front_html_host())
        Args.set_front_html_port(ArgD.get_front_html_port())
        Args.set_after_api_host(ArgD.get_after_api_host())
        Args.set_after_api_port(ArgD.get_after_api_port())
        Args.set_front_html_welcome(ArgD.get_front_html_welcome())
        Args.set_exec_function(ArgD.get_exec_function())
        self.__sizeof__()

    def _version_information(self):
        version = str(self._version_main) + "." + str(self._version_sub) + "." + str(self._version_stage)
        hint("w", "version %s ELF/setup %s" % (version, self.__str__()), False)

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
        print("                          or separated by commas")
        print("ps   : pass is placeholder keyword which used in key-non-value and weak check")
        print("p*ps : ... 为前面的内容可重复")
        print("       <> 为占位参数，里面的内容具有一定的含义")
        print("       [] 为可选参数")
        print("       () 为必选组合")
        print("       | 表示互斥关系只能使用其一")
        print("       pass 为弱占位符，最好不要有其他含义")
        print()
        print("-exec names", Analysis.tgl_func.keys())
        print("ありがとうございました，またねー")

    def _default_analysis(self):
        from system.argument.default import ArgD
        from system.service.conf_tool import ConfigFile
        default_path = ArgD.get_exec_argument()[1]
        default_json = ConfigFile(default_path).get()
        default_version = default_json["version"]
        exec_json = default_json["exec"]
        version = str(self._version_main) + "." + str(self._version_sub) + "." + str(self._version_stage)
        if version != default_version:
            hint("warn", "版本" + version + "与版本" + default_version + "不匹配")
        self._tag_func = Analysis.tgl_func.get(exec_json["function"], lambda x: print("テスト関数"))
        args = exec_json["argument"]
        from system.argument.situation import Args
        Args.set_exec_function(exec_json["function"])
        Args.set_exec_argument(exec_json["argument"])
        self._tag_index = args.__len__()
        self._tag_argv = args

    def start(self):
        self._check = self._check_args()
        if self._check != 1:
            return
        if self._tag_index == 0:
            self._tag_func(None)
        elif Analysis.tgl_max.get(self._tag_func, 0) >= self._tag_index:
            self._tag_func(self._tag_argv)
        else:
            hint("err", "函数" + str(self._tag_func) + "的参数数量" + str(self._tag_index) + "存在异常")

    pass


def register(name, func, num):
    if type(name) == str and type(num) == int:
        Analysis.tgl_func.update({name: func})
        Analysis.tgl_max.update({func: num})
