import datetime


def op_print(level="bug", message="", time=True):
    if time:
        message = datetime.datetime.now().strftime("[%Y-%m-%d %H:%M:%S]") + message
    if level == "out":
        print(":..info.:" + message)
    elif level == "err":
        print(":.error.:" + message)
    elif level == "bug":
        print(":.debug.:" + message)
    else:
        print(":warning:" + message)
    pass
