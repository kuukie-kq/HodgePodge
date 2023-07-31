import datetime


class Config:
    def __init__(self, args):
        self._html_host = "127.0.0.1"
        self._html_port = 50024
        self._api_host = "127.0.0.1"
        self._api_port = 50025
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
                self._html_host = value
            return 1
        elif "--port" == key:
            if "pass" != value:
                self._html_port = int(value)
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
        print("<-warning->", datetime.datetime.now().strftime("[%Y-%m-%d-%H:%M:%S]"), message)
        self.__sizeof__()

    def _error_information(self, message):
        print("<--error-->", datetime.datetime.now().strftime("[%Y-%m-%d-%H:%M:%S]"), message)
        print("==== args :", str(self._arg_size))

    def source(self):
        from system.proxy.html_render import conf as server_config
        server_config(host=self._html_host, port=self._html_port)
        from system.proxy.api_interface import conf as api_config
        api_config(port=self._api_port)

    pass
