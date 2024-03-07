class Args:
    _version_main = -1
    _version_sub = -1
    _version_stage = -1

    _config_file_path = ""

    _front_html_host = ""
    _front_html_port = 0
    _front_html_welcome = ""
    _after_api_host = ""
    _after_api_port = 0

    _exec_function = ""
    _exec_argument = []

    def __init__(self):
        pass

    @staticmethod
    def get_version_main():
        return Args._version_main

    @staticmethod
    def get_version_sub():
        return Args._version_sub

    @staticmethod
    def get_version_stage():
        return Args._version_stage

    @staticmethod
    def get_config_file_path():
        return Args._config_file_path

    @staticmethod
    def get_front_html_host():
        return Args._front_html_host

    @staticmethod
    def get_front_html_port():
        return Args._front_html_port

    @staticmethod
    def get_after_api_host():
        return Args._after_api_host

    @staticmethod
    def get_after_api_port():
        return Args._after_api_port

    @staticmethod
    def get_front_html_welcome():
        return Args._front_html_welcome

    @staticmethod
    def get_exec_function():
        return Args._exec_function

    @staticmethod
    def get_exec_argument():
        return Args._exec_argument

    @staticmethod
    def set_version_main(version_main):
        if type(version_main) == int:
            Args._version_main = version_main

    @staticmethod
    def set_version_sub(version_sub):
        if type(version_sub) == int:
            Args._version_sub = version_sub

    @staticmethod
    def set_version_stage(version_stage):
        if type(version_stage) == int:
            Args._version_stage = version_stage

    @staticmethod
    def set_config_file_path(config_file_path):
        if type(config_file_path) == str:
            Args._config_file_path = config_file_path

    @staticmethod
    def set_config_file_path(config_file_path):
        if type(config_file_path) == str:
            Args._config_file_path = config_file_path

    @staticmethod
    def set_front_html_host(front_html_host):
        if type(front_html_host) == str:
            Args._front_html_host = front_html_host

    @staticmethod
    def set_front_html_port(front_html_port):
        if type(front_html_port) == int:
            Args._front_html_port = front_html_port

    @staticmethod
    def set_after_api_host(after_api_host):
        if type(after_api_host) == str:
            Args._after_api_host = after_api_host

    @staticmethod
    def set_after_api_port(after_api_port):
        if type(after_api_port) == int:
            Args._after_api_port = after_api_port

    @staticmethod
    def set_front_html_welcome(front_html_welcome):
        if type(front_html_welcome) == str:
            Args._front_html_welcome = front_html_welcome

    @staticmethod
    def set_exec_function(exec_function):
        if type(exec_function) == str:
            Args._exec_function = exec_function

    @staticmethod
    def set_exec_argument(exec_argument):
        if type(exec_argument) == list:
            Args._exec_argument = exec_argument

    pass


def front_html_address():
    return "%s:%d" % (Args.get_front_html_host(), Args.get_front_html_port())


def after_api_address():
    return "%s:%d" % (Args.get_after_api_host(), Args.get_after_api_port())


def automatic_html_path():
    return "./static/live/%s" % (Args.get_front_html_welcome())


def log_file_path():
    if Args.get_exec_function() == "pl2d":
        return "./static/free/log.txt"
    elif Args.get_exec_function() == "inst":
        return "./static/free/command.txt"
    else:
        return "2>&1"


def start_argument():
    string = ""
    if Args.get_exec_argument().__len__() % 2 == 0:
        for arg in Args.get_exec_argument():
            string = string + " -argv " + arg
    return string
