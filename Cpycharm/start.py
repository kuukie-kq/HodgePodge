#!/usr/bin/python
import os
import sys
import time

base_workspace = "D:/KuukieProject/first/xxsyprj/server/bin"
fork = "start "
share_memory = True
battle = False


def set_global_value(workspace):
    global base_workspace
    base_workspace = workspace
    # python特性（原则上本文中的全局变量都应该受到写保护）
    # return None
    pass


def pwd_path():
    # command = "pwd"
    command = "echo %cd:\\=/%"
    with os.popen(command) as p:
        workspace = p.readline()
    return ''.join(workspace).strip("\n")


def information_version():
    version = "0.2.0.61"
    print("version ", version, " start.py")
    pass


def information_help():
    print("\nCopyright python 3.8 anaconda3-2022-05 standard module")
    print("==== ==== Create by kuu-kie <3260681415@qq.com> on 20221230\n")
    print("Usage: python start.py [<key> <value>] ...")
    print("==== ====                 key-value help")
    print("-v pass              : display version and continue")
    print("-version pass        : same as -v")
    print("-h pass              : display help and continue")
    print("-help pass           : same as -h")
    print("-share pass          : do not start share memory server")
    print("-battle pass         : start bn server (bn server starter mode)")
    print("-pwd [pass | <path>] : use current directory (and path) spliced into workspace")
    print("-dir <path>          : use path as workspace")
    print("ps   : pass is placeholder keyword which used in key-non-value and weak check")
    print("pps  : it is necessary to use -pwd or -dir when have any args")
    print("==== ====")
    print("p*ps : ... 为前面的内容可重复")
    print("       <> 为占位参数，里面的内容具有一定的含义")
    print("       [] 为可选参数")
    print("       () 为必选组合")
    print("       | 表示互斥关系只能使用其一")
    print("       pass 为弱占位符，最好不要有其他含义")
    print("\nありがとうございました，またねー")
    pass


def information_error(message):
    print(message)
    print("特别注意！！！see help")
    pass


def start_g_logger_d(configuration):
    logger_workspace = "/glogger/"
    run = "glogger_d.exe "
    command = fork + base_workspace + logger_workspace + run + base_workspace + logger_workspace + configuration
    with os.popen(command) as p:
        pass


def start_basic_dbs4game():
    basic_workspace_dbs4game = "/DBS4Game/"
    run = "DBS4Game_d.exe "
    command = fork + base_workspace + basic_workspace_dbs4game + run
    with os.popen(command) as p:
        pass


def start_basic_xverifycode():
    # basic_workspace_xverifycode = "/XVerifyCode/"
    # run = "XVerifyCode.exe "
    # configuration = "vc_cfg.txt"
    # command = fork + base_workspace + basic_workspace_xverifycode + run
    # + base_workspace + basic_workspace_xverifycode + configuration
    # with os.popen(command) as p:
    #    pass
    pass


def start_basic_xlba():
    basic_workspace_xlba = "/XLBA/"
    run = "XLBA.exe "
    configuration = "lba_cfg.txt"
    command = fork + base_workspace + basic_workspace_xlba + run + base_workspace + basic_workspace_xlba + configuration
    with os.popen(command) as p:
        pass


def start_basic_xnp():
    basic_workspace_xnp = "/XNP/"
    run = "XNP.exe "
    configuration = "np_cfg.txt"
    command = fork + base_workspace + basic_workspace_xnp + run + base_workspace + basic_workspace_xnp + configuration
    with os.popen(command) as p:
        pass


def start_global_gms4game():
    global_workspace_gms4game = "/GMS4Game/"
    run = "GMS4Game_d.exe "
    command = fork + base_workspace + global_workspace_gms4game + run
    with os.popen(command) as p:
        pass


def start_global_xgmgs():
    global_workspace_xgmgs = "/XGMGS/"
    run = "XGMGS.exe "
    configuration = "gmgs_cfg.txt"
    command = fork + base_workspace + global_workspace_xgmgs + run + base_workspace + global_workspace_xgmgs + configuration
    with os.popen(command) as p:
        pass


def start_global_xgis():
    global_workspace_xgis = "/XGIS/"
    run = "XGIS.exe "
    configuration = "gis_cfg.txt"
    command = fork + base_workspace + global_workspace_xgis + run + base_workspace + global_workspace_xgis + configuration
    with os.popen(command) as p:
        pass


def start_gms_xshmsvr():
    gms_workspace_xshmsvr = "/XSHMSVR/"
    run = "XSHMSVR_d.exe "
    command = fork + base_workspace + gms_workspace_xshmsvr + run
    with os.popen(command) as p:
        pass


def start_gms_xgms():
    gms_workspace_xgms = "/XGMS/"
    run = "XGMS.exe "
    configuration = "gms_cfg.txt"
    command = fork + base_workspace + gms_workspace_xgms + run + base_workspace + gms_workspace_xgms + configuration
    with os.popen(command) as p:
        pass


def start_gms_xcaafs2():
    gms_workspace_xcaafs2 = "/XCAAFS2/"
    run = "XCAAFS2_d.exe "
    configuration = "caafs2_cfg1.txt"
    command = fork + base_workspace + gms_workspace_xcaafs2 + run + base_workspace + gms_workspace_xcaafs2 + configuration
    with os.popen(command) as p:
        pass


def start_gms_xcls():
    gms_workspace_xcls2 = "/XCLS2/"
    run = "XCLS2_d.exe "
    configuration = "cls2_cfg1.txt"
    command = fork + base_workspace + gms_workspace_xcls2 + run + base_workspace + gms_workspace_xcls2 + configuration
    with os.popen(command) as p:
        pass


def start_gms_xgbnms():
    xgbnms_workspace = "/XGBNMS/"
    run = "XGBNMS.exe "
    configuration = "gbnms_cfg.txt"
    command = fork + base_workspace + xgbnms_workspace + run + base_workspace + xgbnms_workspace + configuration
    with os.popen(command) as p:
        pass


# 由于Nginx本身的原因? 这种方式的启动起不起来，故不在这里控制启动
# nginx_workspace = "/openresty/openresty_inner/"


def start_gzs_d(configuration):
    xgzs_workspace = "/vc141debugs/"
    run = "XGZS_d.exe "
    command = fork + base_workspace + xgzs_workspace + run + base_workspace + xgzs_workspace + configuration
    with os.popen(command) as p:
        pass


def start_g_logger():
    start_g_logger_d("glogger_cfg_00_cmn.txt")
    start_g_logger_d("glogger_cfg_01_error.txt")
    start_g_logger_d("glogger_cfg_02_story.txt")
    start_g_logger_d("glogger_cfg_03_hack.txt")
    start_g_logger_d("glogger_cfg_04_fatal.txt")
    start_g_logger_d("glogger_cfg_05_datarecover.txt")
    start_g_logger_d("glogger_cfg_06_billing.txt")
    start_g_logger_d("glogger_cfg_07_player.txt")
    start_g_logger_d("glogger_cfg_08_fight.txt")
    start_g_logger_d("glogger_cfg_09_item.txt")
    start_g_logger_d("glogger_cfg_10_npc.txt")
    start_g_logger_d("glogger_cfg_11_clan.txt")
    start_g_logger_d("glogger_cfg_12_talk.txt")
    start_g_logger_d("glogger_cfg_13_gm.txt")
    start_g_logger_d("glogger_cfg_14_survey.txt")


def start_basic():
    start_basic_dbs4game()
    # start_basic_xverifycode()
    start_basic_xlba()
    start_basic_xnp()


def start_global():
    start_global_gms4game()
    start_global_xgmgs()
    start_global_xgis()


def start_gms():
    if share_memory:
        start_gms_xshmsvr()
    start_gms_xgms()
    time.sleep(5)
    start_gms_xcaafs2()
    time.sleep(5)
    start_gms_xcls()
    if battle:
        start_gms_xgbnms()


def start_gzs():
    start_gzs_d("../data/cfg/network/cfg_home.txt")
    start_gzs_d("../data/cfg/network/cfg_misc.txt")
    start_gzs_d("../data/cfg/network/cfg_relation.txt")
    start_gzs_d("../data/cfg/network/cfg_scn.txt")


def start():
    print("xxsy service project automatic starter")
    print("It will take a few more steps to complete")
    for i in iter(int, 1):
        print("\n\n")
        if not share_memory:
            i = i + 1
        if battle:
            i = i + 2
        print(i)
        print("\n\n")
        print("1 Which mode do you want to start in? If you select all, start all servers.")
        first = input("please select : ")
        if "all" == first:
            start_g_logger()
            time.sleep(2)
            start_basic()
            time.sleep(2)
            start_global()
            time.sleep(2)
            start_gms()
            time.sleep(2)
            start_gzs()
        elif "exit" == first or "quit" == first:
            break
        else:
            print("2 {15logs} Determine if you have started (no/0) or want to start (yes/1).")
            second = input("please select : ")
            if "yes" == second or "1" == second:
                start_g_logger()
            print("3 {3basic(1)} Determine if you have started (no/0) or want to start (yes/1).")
            third = input("please select : ")
            if "yes" == third or "1" == third:
                start_basic()
            elif "no" == third or "0" == third:
                pass
            else:
                print("3.1 {DBS4Game} Determine if you have started (no/0) or want to start (yes/1).")
                third_one = input("please select : ")
                if "yes" == third_one or "1" == third_one:
                    start_basic_dbs4game()
                print("3.2 {XLBA} Determine if you have started (no/0) or want to start (yes/1).")
                third_two = input("please select : ")
                if "yes" == third_two or "1" == third_two:
                    start_basic_xlba()
                print("3.3 {XNP} Determine if you have started (no/0) or want to start (yes/1).")
                third_three = input("please select : ")
                if "yes" == third_three or "1" == third_three:
                    start_basic_xnp()
                # 分步启动完成
                pass
            print("4 {3global} Determine if you have started (no/0) or want to start (yes/1).")
            fourth = input("please select : ")
            if "yes" == fourth or "1" == fourth:
                start_global()
            elif "no" == fourth or "0" == fourth:
                pass
            else:
                print("4.1 {GMS4Game} Determine if you have started (no/0) or want to start (yes/1).")
                fourth_one = input("please select : ")
                if "yes" == fourth_one or "1" == fourth_one:
                    start_global_gms4game()
                print("4.2 {XGMGS} Determine if you have started (no/0) or want to start (yes/1).")
                fourth_two = input("please select : ")
                if "yes" == fourth_two or "1" == fourth_two:
                    start_global_xgmgs()
                print("4.3 {XGIS} Determine if you have started (no/0) or want to start (yes/1).")
                fourth_three = input("please select : ")
                if "yes" == fourth_three or "1" == fourth_three:
                    start_global_xgis()
                # 分步启动完成
                pass
            print("5 {4gms} Determine if you have started (no/0) or want to start (yes/1).")
            fifth = input("please select : ")
            if "yes" == fifth or "1" == fifth:
                start_gms()
            elif "no" == fifth or "0" == fifth:
                pass
            else:
                print("5.1 {XSHMSVR} Determine if you have started (no/0) or want to start (yes/1).")
                fifth_one = input("please select : ")
                if "yes" == fifth_one or "1" == fifth_one:
                    start_gms_xshmsvr()
                print("5.2 {XGMS} Determine if you have started (no/0) or want to start (yes/1).")
                fifth_two = input("please select : ")
                if "yes" == fifth_two or "1" == fifth_two:
                    start_gms_xgms()
                print("5.3 {XCAAFS2} Determine if you have started (no/0) or want to start (yes/1).")
                fifth_three = input("please select : ")
                if "yes" == fifth_three or "1" == fifth_three:
                    start_gms_xcaafs2()
                print("5.4 {XCLS2} Determine if you have started (no/0) or want to start (yes/1).")
                fifth_four = input("please select : ")
                if "yes" == fifth_four or "1" == fifth_four:
                    start_gms_xcls()
                print("5.5 {XGBNMS} Determine if you have started (no/0) or want to start (yes/1).")
                fifth_five = input("please select : ")
                if "yes" == fifth_five or "1" == fifth_five:
                    start_gms_xgbnms()
                # 分步启动完成
                pass
            print("6 {4gzs} Determine if you have started (no/0) or want to start (yes/1).")
            sixth = input("please select : ")
            if "yes" == sixth or "1" == sixth:
                start_gzs()
            pass
        # 死循环内 一次循环的末尾 pass的用处
        # 注意python中如何使用for实现死循环
        pass
    print("ありがとうございました")
    pass


def check_args():
    arg_size = len(sys.argv)
    if arg_size == 1:
        return 1
    elif arg_size % 2 == 1:
        flag = 0
        for i in range(1, arg_size, 2):
            arg_key = sys.argv[i]
            arg_value = sys.argv[i + 1]
            if "-dir" == arg_key:
                print("==== ==== !\n", arg_value)
                condition = input("warning !!! please make sure the last line path is valid (Enter) : ")
                if "" == condition and flag == 0:
                    set_global_value(arg_value)
                    flag = 1
                else:
                    information_error("-dir 参数解析异常")
                    return 0
                pass
            elif "-pwd" == arg_key:
                if "pass" == arg_value:
                    path_value = pwd_path()
                else:
                    path_value = pwd_path() + arg_value
                print("==== ==== !\n", path_value)
                condition = input("warning !!! please make sure the last line path is valid (Enter) : ")
                if "" == condition and flag == 0:
                    set_global_value(path_value)
                    flag = 1
                else:
                    information_error("-pwd 参数解析异常")
                    return 0
                pass
            elif "-battle" == arg_key:
                if "pass" != arg_value:
                    information_error("key-value error")
                    return 0
                global battle
                battle = True
            elif "-share" == arg_key:
                if "pass" != arg_value:
                    information_error("key-value error")
                    return 0
                global share_memory
                share_memory = False
            elif "-v" == arg_key or "-version" == arg_key:
                if "pass" != arg_value:
                    information_error("key-value error")
                    return 0
                information_version()
            elif "-h" == arg_key or "-help" == arg_key:
                information_help()
                if "pass" != arg_value:
                    information_error("key-value error")
                    return 0
            else:
                print("unknow key:", arg_key, " & value:", arg_value)
                information_help()
            # 循环内 一次循环的末尾
            pass
        return flag
    else:
        information_error("存在无效的参数")
        return 0
    pass


if __name__ == '__main__':
    if check_args() == 1:
        start()
        # pass的另一种用法debugger，debug测试的时候将上面注释掉，pass是可以断点的
        pass
    # 使用说明
    # 通过python，代替脚本，避免脚本的部分逻辑编写困难的问题
    # 编写日志：
    # ====2022-08-18 version 0.0.1 完成最基本的windows全部服务器的启动
    # ====2022-08-19 version 0.0.2 代码基本检查，主要关注警告内容
    # ====2022-08-29 version 0.0.3 代码重新整理，并且提示信息稍微完善
    # ====2022-09-23 version 0.1.0 对一些开源软件学习后，增加一个退出关键字quit
    # ====2022-12-28 version 0.1.1 修改每次循环内输出的数字
    # ====2022-12-29 version 0.1.2 增加自动获取基目录，main参数处理&校验
    # ====2022-12-30 version 0.1.3 维护help，将本地服务器与竞技服务器合起来
    # ====2023-01-03 version 0.1.4 补充一些兼容Linux的部分
    # ====2023-01-05 version 0.1.5 完善help部分代码review
    # ====2023-01-06 version 0.2.0 全面测试，并修改细节
    # 注意事项：
    # ====2022-08-18 使用死循环，唯一退出关键字exit，且只有在第一步的时候才能退出
    # ====  0.0.1 注意，这是特意这样写的
    # ====2022-08-19 整体代码微调，（）符号为习惯，虽然可以不要但保留，with语句返回的文件描述符不一定需要，但保留
    # ====  0.0.2 目前来说基本完成了需求，考虑到方便性，需要配合bat使用
    # ====2022-09-23 if的条件去掉了括号，因为语法上与或与有括号的语言有区别
    # ====  0.1.0 exit与quit为退出关键字
    # ====2022-12-28 该条目时间乱了，由于仅为小细节部分，作为提示信息的作用，所以为历史时间
    # ====  0.1.1 0本地服务器，1本地服务器（多组情况），2竞技服务器（也作为本地服务器），3竞技服务器（多组情况）
    # ====2022-12-29 基目录以本程序文件start.py所在目录为基准，且不能存在含有特殊字符（空格）的路径
    # ====  0.1.2 原则上main的参数是成对出现的，既key-value模式，如果version等只有key的情况，则可以使用pass关键字作为占位填充value，未对help信息进行维护
    # ====2022-12-30 各个参数的作用，必要情况需要配合使用，逻辑上本地服务器与竞技服务器是相同的，但是程序中的分步启动模式却是都可以的
    # ====  0.1.3 与无参数版本一样，默认情况是启动本地服务器，由全局变量来控制，原则上同时也是静态变量
    # ====2023-01-03 尝试一些linux与win相互对应的部分，如果使用参数，则默认情况并不会启动服务器，需要指定-dir或-pwd参数且确认路径没问题才行
    # ====  0.1.4 实际上并不能兼容，因为启动的服务器linux版需要另行编译，结果也与win存在区别.exe
    # ====2023-01-06 注意使用参数和不使用参数的区别，不使用参数相当于0.1.0版本的用法，而使用参数则是另外一套用法
    # ====  0.2.0 pwd参数的作用是获取当前shell环境的目录，如果是通过bat启动的，则bat所在的位置要对应得上才行
    pass
