import datetime


class Config:
    """
    配置文件相关
    用于-argv中配置的main参数的分析
    """
    def __init__(self, args):
        self._host = "127.0.0.1"
        self._port = 50024
        # 变量
        self._arg_size = args.__len__()
        self._arg_array = args
        self.error = 0
        self.check = self._check_args()

    def _check_args(self):
        if self._arg_size % 2 != 0:
            self.error = 2
            return 0
        else:
            for i in range(0, self._arg_size, 2):
                arg_key = self._arg_array[i]
                arg_value = self._arg_array[i + 1]
                arg_flag = self._args_analysis(arg_key, arg_value)
                if arg_flag == 2:
                    self.error = 12
                    return 0
                elif arg_flag == 0:
                    break
        return 1

    def _args_analysis(self, key, value):
        """0:break 1:continue 2:exit"""
        if "--host" == key:
            if "pass" != value:
                self._host = value
            return 1
        elif "--port" == key:
            if "pass" != value:
                self._port = int(value)
            return 1
        elif "--conf" == key:
            conf_path = "./static/live2d"
            if "pass" != value:
                conf_path = value
            print("pass (Config-_args_analysis--conf)")
            return 1
        else:
            return 2

    def _warning_information(self, message):
        print("<-->" + datetime.datetime.now().strftime("%Y-%m-%d") + message)
        self.__sizeof__()

    def _error_information(self, message):
        print("<**>" + datetime.datetime.now().strftime("%Y-%m-%d") + message)
        print("==== args:" + str(self._arg_size))

    def flag(self):
        return self.check == 1

    def source(self):
        from system.server.proxy_html import conf as server_config
        server_config(host=self._host, port=self._port)

    pass
