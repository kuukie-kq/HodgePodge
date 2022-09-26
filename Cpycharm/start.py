import os
import time

base_workspace = "D:/KuukieProject/first/xxsyprj/server/bin"
fork = "start "


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
    start_gms_xshmsvr()
    start_gms_xgms()
    time.sleep(5)
    start_gms_xcaafs2()
    time.sleep(5)
    start_gms_xcls()


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


if __name__ == '__main__':
    start()
    # 使用说明
    # 通过python，代替脚本，避免脚本的部分逻辑编写困难的问题
    # 编写日志：
    # ====2022-08-18 version 0.0.1 完成最基本的windows全部服务器的启动
    # ====2022-08-19 version 0.1.0 整体代码微调（）符号为习惯，虽然可以不要但保留，with语句返回的文件描述符不一定需要，但保留
    # ====2022-08-29 version 0.1.1 代码重新整理，并且提示信息稍微完善
    # ====2022-09-23 version 0.1.2 对一些开源软件学习后，增加一个退出关键字quit
    # 注意事项：
    # ====2022-08-18 使用死循环，唯一退出关键字exit，且只有在第一步的时候才能退出
    # ====           0.0.1 注意，这是特意这样写的
    # ====2022-09-23 if的条件去掉了括号，因为语法上与或与有括号的语言有区别
    # ====           0.1.2 exit与quit为退出关键字
    pass
