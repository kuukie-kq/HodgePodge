# 学习笔记&说明文档
首先学习使用markdown规范，同时作为学习其他工具例如gdb相关的说明
# Contents
>
> [1 markdown](#markdown "当前文档中的标题")
>
> > [1.1 markdown说明](#markdown说明 "当前文档中的标题")
> >
> > [1.2 markdown其他](#markdown其他 "当前文档中的标题")
>
> [2 gdb](#gdb "当前文档中的标题")
>
# 正文

## MarkDown

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

``` -> markdown
##
##

####

######
```

- 换行

``` -> markdown
######

######
```

> or

``` -> markdown
######<br>
```

- 引用&链接

``` -> markdown
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

``` -> markdown
![官网示例图片](https://markdown.com.cn/hero.png "MD logo")
```

### MarkDown说明

****

整体感受很舒服

并且markdown基本原理，是基于html的方式渲染的<br>
既markdown标记语言转成html标签语言<br>
因此也可以内嵌html标签的方式来自定义样式

如果记住之后用好markdown还是很方便的

目前感觉唯一不方便的点是有些格式需要多空一些行<br>
而有时候这些行却并不是编写者的语义（代码中空行）

### MarkDown其他

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

****
