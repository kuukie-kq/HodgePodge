class ArgumentDefaultMeta(type):
    # from enum import Enum 可以仿照EnumMeta中的EnumDict将属性设置为const
    pass


class ArgD(metaclass=ArgumentDefaultMeta):
    _version_main = 0
    _version_sub = 0
    _version_stage = 0

    _config_file_path = "./static/config/default"

    _front_html_host = "127.0.0.1"
    _front_html_port = 50024
    _front_html_welcome = "trash.html"
    _after_api_host = "127.0.0.1"
    _after_api_port = 50025

    _exec_function = "pl2d"
    _exec_argument = ["--conf", "./static/config/default"]

    def __init__(self):
        pass

    @staticmethod
    def get_version_main():
        return ArgD._version_main

    @staticmethod
    def get_version_sub():
        return ArgD._version_sub

    @staticmethod
    def get_version_stage():
        return ArgD._version_stage

    @staticmethod
    def get_config_file_path():
        return ArgD._config_file_path

    @staticmethod
    def get_front_html_host():
        return ArgD._front_html_host

    @staticmethod
    def get_front_html_port():
        return ArgD._front_html_port

    @staticmethod
    def get_after_api_host():
        return ArgD._after_api_host

    @staticmethod
    def get_after_api_port():
        return ArgD._after_api_port

    @staticmethod
    def get_front_html_welcome():
        return ArgD._front_html_welcome

    @staticmethod
    def get_exec_function():
        return ArgD._exec_function

    @staticmethod
    def get_exec_argument():
        return ArgD._exec_argument

    pass
