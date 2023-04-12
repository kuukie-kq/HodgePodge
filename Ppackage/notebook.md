# 学习笔记&说明文档

首先学习使用markdown规范，同时作为学习其他工具例如gdb相关的说明

# Contents

>
> [1 markdown](#markdown "当前文档中的标题")
>
> > [1.1 markdown基本语法](#1基本语法 "当前文档中的标题")
> >
> > [1.2 markdown扩展语法](#1扩展语法 "当前文档中的标题")
> >
> > [1.3 markdown说明](#1说明 "当前文档中的标题")
> >
> > [1.4 markdown其他](#1其他 "当前文档中的标题")
>
> [2 gdb](#gdb "当前文档中的标题")
>
> > [2.1 gdb简单用法](#2简单用法 "当前文档中的标题")
>
> [3 Unicode](#unicode "当前文档中的标题")
>
> > [3.1 Unicode统一码](#3统一编码库 "当前文档中的标题")
>
> > [3.2 UTF-8](#3utf8编码 "当前文档中的标题")
>
> [4 Lua](#lua "当前文档中的标题")
>
> > [4.1 Lua基础语法](#4lua基础 "当前文档中的标题")
>
> > [4.2 Lua与C/C++的相互调用](#4调用 "当前文档中的标题")
>
> [5 Linux](#linux "当前文档中的标题")
>
> > [5.1 [linux+10]系统性能分析&工具](#5性能分析 "当前文档中的标题")
>
> > [5.2 [Linux+1]定时任务](#5定时任务相关 "当前文档中的标题")
>
> > [5.3 断言](#5cc断言 "当前文档中的标题")
>

# 正文

## MarkDown

### 1基本语法

****

- [MarkDown官方教程](https://markdown.com.cn/basic-syntax/ "官网教程")

参考最佳实践整理部分常用笔记

- 标题

``` markdown
#
##
###
####
#####
######
```

- 段落

``` markdown
##
##

####

######
```

- 换行

``` markdown
######

######
```

> or

``` markdown
######<br>
```

- 引用&链接

``` markdown
>
> [1. markdown](#markdown "当前文档中的标题")
>
> [2. markdown使用](#markdown使用 "当前文档中的标题")
>
> > [2.1 学习笔记说明文档](#学习笔记说明文档 "当前文档中的标题")
> >
> > [2.2 学习笔记说明文档2](#学习笔记说明文档2 "当前文档中的标题")
>
```

- 列表

> ol

``` markdown
1. 
5. 
5. 
5. 
```

> ul

``` markdown
- 
- 
- 
```

- 分割线

``` markdown
****
```

- 图片

与链接相似，区别在于前面有个！符号，值得注意的是一般图片的路径很容易变化（除非是官网等资源）容易造成图片无法显示的情况

``` markdown
![官网示例图片](https://markdown.com.cn/hero.png "MD logo")
```

### 1扩展语法

****

- [MarkDown官方扩展教程](https://markdown.com.cn/extended-syntax/ "官网教程")

- 表格

``` markdown
|   name    | language |  editor   | sub |
|:---------:|:--------:|:---------:|:---:|
|   clion   |  C/C++   |   CLion   |  L  |
|   idea    |   Java   |   Idea    |  I  |
|  pycharm  |  Python  |  PyCharm  |  P  |
| hbuilderx |   Html   | HBuilderX |  H  |
```

- 删除线

``` markdown
~~不是~~
```

- 围栏代码块

```
` ` ` key
key code
` ` `
```

### 1说明

****

整体感受很舒服

并且markdown基本原理，是基于html的方式渲染的<br>
既markdown标记语言转成html标签语言<br>
因此也可以内嵌html标签的方式来自定义样式

如果记住之后用好markdown还是很方便的

目前感觉唯一不方便的点是有些格式需要多空一些行<br>
而有时候这些行却并不是编写者的语义（代码中空行）

本文的编写格式习惯参照GitHub的GitHub&nbsp;Flavored&nbsp;Markdown&nbsp;(GFM)

github md 例如#与##的标题自带一个```<hr \>```标签（实际上应该是h标签的样式加了border-bottom形成的一个类似的线）但在vscode预览中只有#有

突然发现可以作为网址收藏专用夹

### 1其他

****

$$\sum_{n=1}^{100} n$$

$$f(x) = sin(x) + 10$$

``` flow
st=>start: 开始框
op=>operation: 处理框
cond=>condition: 判断框(是或否?)
sub1=>subroutine: 子流程
io=>inputoutput: 输入输出框
e=>end: 结束框
st->op->cond
cond(yes)->io->e
cond(no)->sub1(right)->op
```

## gdb

### 2简单用法

****

- [同样也有相应的说明文档](https://zhuanlan.zhihu.com/p/297925056 "知乎-GDB使用")

整理部分常用笔记

- debug

``` shell
gdb shfilename corefilename
```

- 查看断点堆栈信息

``` gdb
backtrace
```

> or

``` gdb
bt
```

- 选择栈层，查看更加详细内容

``` gdb
frame 0
```

> or

``` gdb
f 0
```

- 查看源码信息，编译的时候添加的有-g参数才能看到

``` gdb
list
```

> or

``` gdb
l
```

- 查看一些运行时的信息

``` gdb
info
```

> or

``` gdb
i
```

- 打印变量信息

``` gdb
p namespace::pointer->pointer->array[2237]->pointer->pointer

print *pointer

p *(StructName*)pointer

p *(StructName*)0xe0a8600e
```

- 退出

``` gdb
quit
```

> or

``` gdb
q
```

- 查看汇编

``` gdb
disassemble
```

> or

``` gdb
dis
```

## Unicode

### 3统一编码库

****

[统一码编码库](https://fuhaoku.net/blocks "符号库")

- 预计编码量 $$17 * 65536 = 1114112$$ 所以需要21位

### 3UTF8编码

****

| byte size |               format                | coding bit |      range      |
|:---------:|:-----------------------------------:|:----------:|:---------------:|
| 1         | 0xxxxxxx                            |  7         | 0 ~ 127         |
| 2         | 110xxxxx 10xxxxxx                   | 11         | 128 ~ 2047      |
| 3         | 1110xxxx 10xxxxxx 10xxxxxx          | 16         | 2048 ~ 65535    |
| 4         | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx | 21         | 65536 ~ 2097151 |

- 例如：汉的统一码编码是0x6C49，为27721在2048 ~ 65535使用3字节，二进制为0110&nbsp;1100&nbsp;0100&nbsp;1001放入模板中为11100110&nbsp;10110001&nbsp;10001001既0xE6B189（汉的UTF8编码）

## Lua

### 4Lua基础

****

``` lua
print("Hello World")

Entity = { length = 0, breadth = 0, height = 0 }

function Entity:new()
	o = {}
	setmetatable(o, self)
	self.__index = self
	self.length = 0
	self.breadth = 0
	self.height = 0
	return o
end

function Entity:display()
	print("面积/体积为", self.length * self.breadth * self.height )
end

Bool = Entity:new()

function Bool:new()
	o = Entity:new()
	setmetatable(o, self)
	self.__index = self
	self.message = "圆形"
	return o
end

function Bool:display()
	print(self.message , "面积为", self.length * self.length * 355 / 113)
end

test = Entity:new()

test.length = 10
test.breadth = 5
test.height = 8

t = Bool:new()
t.length = 3.847
t.message = "基于实体的圆形"

test:display()
t:display()
```

### 4调用

****

- Lua部分（cluac_lua.lua）

``` lua
function lua_c(a, b)
	print("<- lua call c function (running) >")
	print("arg[0]", a, "arg[1]", b)
	avg, sum = lu_average(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
	return avg, sum
end

function c_lua(a, b)
	print("<* lua function is called (running) >")
	return lua_c(a, b)
end

-- test
print("lua start")
```

- C/C++部分（cluac_c.cpp）

``` C++
#include <iostream>
#include <math.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
};

int c_lu_average(lua_State* L) {
	int n = lua_gettop(L);
	double sum = 0;
	for (int i=1;i<=n;i++) {
		if (!lua_isnumber(L,i)) { lua_pushstring(L,"average incorrect args"); lua_error(L); }
		sum = sum + lua_tonumber(L,i);
	}
	double svg = sum / n;
	std::cerr << svg << std::endl;
	lua_pushnumber(L,svg);
	lua_pushnumber(L,sum);
	return 2;
}

lua_State* Lua = nullptr;

void binding() {
	if (Lua != nullptr) { std::cerr << "初始化失败" << std::endl; return; }
	Lua = luaL_newstate();
	luaL_openlibs(Lua);
	lua_register(Lua,"lu_average", c_lu_average);
}

void release() {
	lua_close(Lua);
}

int main() {
	binding();

	luaL_dofile(Lua, "cluac_lua.lua");
	lua_getglobal(Lua, "c_lua");
	lua_pushnumber(Lua, 1);
	lua_pushnumber(Lua, 10);
	lua_pcall(Lua,2,2,0);

	int result_sum = lua_tointeger(Lua,-1);
	lua_pop(Lua,1);
	int result_avg = lua_tointeger(Lua,-1);
	lua_pop(Lua,1);

	std::cout << "和为" << result_sum << "平均数为" << result_avg << std::endl;

	release();
	return 0;
}
```

## Linux

### 5性能分析

****

sysstat包

[sar命令相关](https://cloud.tencent.com/developer/article/1513543 "")

注意与其他系统监控工具（glibc）的区别

### 5定时任务相关

****

附：[Linux系统相关命令](https://www.runoob.com/linux/linux-command-manual.html "菜鸟教程-Linux命令大全")

附：[Linux相关源码](https://elixir.bootlin.com/ "bootlin-kernel&glibc")

- 查找定时任务服务进程

``` shell
kuukie@ubuntu:~> ps aux | grep crond | grep -v grep
root      3388  0.0  0.0 114940  1028 ?        Ss    2022   0:38 crond
kuukie@ubuntu:~> 
```

- 查看&设定的定时任务

``` shell
kuukie@ubuntu:~> crontab -l
kuukie@ubuntu:~> crontab -e
# append
* * * * * ps aux >> /opt/ps.kaof 2>&1
kuukie@ubuntu:~> sudo touch /opt/ps.kaof
kuukie@ubuntu:~> sudo chmod 666 /opt/ps.kaof
kuukie@ubuntu:~> sudo service --help
kuukie@ubuntu:~> sudo service --status-all
kuukie@ubuntu:~> sudo service cron start
kuukie@ubuntu:~> cat /dev/null > /opt/ps.kaof
```

- 遇到的一些问题

> 定时任务服务crond(cron)需要启动才行
>
> crond为较早版本，新版本名为cron（未从网上得到证实）为GUN相关用户程序

- 原理

[源码？miscutils/crond.c](https://github.com/mirror/busybox/ "busybox")

### 5C/C++断言

***

巧妙的应用

``` C
#include <assert.h>
(void) ((!!0) || (_assert("test", __FILE__, __LINE__), 0));
```

``` shell
readlink /proc/self/exe
```

### 5命令大全

****

[linux命令大全](https://www.runoob.com/linux/linux-command-manual.html "菜鸟教程")

[Redis相关操作](https://blog.csdn.net/Dance_sheng/article/details/118904661 "CSDN")

# 总结

markdown的解释器有各种各样的，其中规范支持的部分官网中已经给出了标准示例，但还是有一些语法在不同环境下的效果不太一样

# 待研究

[帧同步系统-相关](https://zhuanlan.zhihu.com/p/556920018 "知乎")

[kcp相关-使用设计需考虑问题](https://github.com/skywind3000/kcp/issues/100 "GitHub-issue")
