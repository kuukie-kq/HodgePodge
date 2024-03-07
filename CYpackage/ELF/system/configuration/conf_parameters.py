class Config:
    def __init__(self, args):
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
        from system.argument.situation import Args
        if "--host" == key:
            if "pass" != value:
                Args.set_front_html_host(value)
            return 1
        elif "--port" == key:
            if "pass" != value:
                Args.set_front_html_port(int(value))
            return 1
        elif "--conf" == key:
            from system.service.conf_tool import ConfigFile
            if "pass" != value:
                Args.set_config_file_path(value)
            conf_json = ConfigFile(Args.get_config_file_path())
            html = conf_json.get_front()
            Args.set_front_html_host(html["host"])
            Args.set_front_html_port(html["port"])
            api = conf_json.get_after()
            Args.set_after_api_host(api["host"])
            Args.set_after_api_port(api["port"])
            if html["welcome"] is not None:
                Args.set_front_html_welcome(html["welcome"])
            return 1
        else:
            return 2

    def source(self):
        self.__sizeof__()
        from system.service.conf_tool import TempLive2d
        trash = TempLive2d()
        trash.construction()

    pass
