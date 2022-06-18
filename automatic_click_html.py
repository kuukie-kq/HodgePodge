from selenium import webdriver
from selenium.webdriver.support.select import Select
import time

"""
Created by kuukie on 2022/06/04
说明：
程序依赖  Linux系统下，自带火狐浏览器
运行环境  anaconda库，python3.8版本

运行前请修改代码中的相应字符串

代码说明：
selenium为封装好的模拟键盘鼠标事件的库
首先加载驱动，与火狐浏览器相连，驱动为GitHub上的开源包
然后访问网页
接着循环输入表单数据，提交，返回
缺点：
需要程序跑起来后一直盯着看没有做找到后的break
time的作用就是适当的调一下速度，让

更新V1：
可以做到找到后break
运行时可以把time.sleep去掉，直接飞速跑
"""

browser = webdriver.Firefox(executable_path="/home/kuukie/PycharmProjects/AutomaticClick/geckodriver-v0.31.0-linux64/geckodriver")
browser.get("https://www.miiteec.org.cn/plus/list.php?tid=247")

for i in range(0, 1000):
    el1_s = Select(browser.find_element_by_id("kaoshi"))
    el2_s = Select(browser.find_element_by_id("zhengshu"))
    el3 = browser.find_element_by_id("identify")
    el4 = browser.find_element_by_id("proof")
    el5 = browser.find_element_by_id("submit")

    el1_s.select_by_value("3")
    el2_s.select_by_value("309")
    el3.send_keys("370***********6629")
    if i < 10:
        el4.send_keys("L210020100200" + "00" + str(i))
    elif i < 100:
        el4.send_keys("L210020100200" + "0" + str(i))
    else:
        el4.send_keys("L210020100200" + str(i))
    el5.click()

    time.sleep(0)

    el_r = browser.find_element_by_class_name("plist2_p")
    result = False
    l_el_r = el_r.find_elements_by_xpath("div/label")
    d_el_r = el_r.find_elements_by_xpath("div")
    for label in l_el_r:
        result = True
    if result:
        for div in d_el_r:
            print(div.text)
        break
    browser.back()
