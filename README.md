# HodgePodge

#### instruction

- fatal: unable to access 'https://github.com/kuukie-kq/HodgePodge.git/': Failed to connect to github.com port 443 after 21088 ms: Timed out

- fatal: unable to access 'https://github.com/kuukie-kq/HodgePodge.git/': OpenSSL SSL_read: Connection was reset, errno 10054

- error: RPC failed; curl 28 OpenSSL SSL_read: Connection was reset, errno 10054 fatal: expected flush

****

以上三种报错都与网络有关，首先通过浏览器看看是否为不可访问，如果没有问题则跟本地环境配置有关
有ssl校验和http代理等影响，主要修改$HOME/.gitconfig文件

``` shell
git config --global http.version HTTP/1.1
git clone --depth=1 https://github.com/kuukie-kq/HodgePodge e:/GitHub/kuukie-kq/HodgePodge
git fetch --unshallow
```

- .gitconfig

``` conf
[http]
	version = HTTP/1.1

```

#### 7s

CDEFGAB -> 0xCDEF7AB

###### Directory

- C -> code
- P -> public
- S -> summer

|   name    | language |  editor   | sub |
|:---------:|:--------:|:---------:|:---:|
|   clion   |  C/C++   |   CLion   |  L  |
|   idea    |   Java   |   Idea    |  I  |
|  pycharm  |  Python  |  PyCharm  |  Y  |
| hbuilderx |   Html   | HBuilderX |  H  |

****

用于学习参考主要放比较经典有用的，有笔记，有小程序，也有小项目，比较杂乱（大杂烩）

## PostScript

注意到GitHub中的Issue PullRequest & Actions & Projects的功能，尝试学习使用

vscode ctrl+shift+v 开启预览
