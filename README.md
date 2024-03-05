# HodgePodge

#### instruction

- fatal: unable to access 'https://github.com/kuukie-kq/HodgePodge.git/': Failed to connect to github.com port 443 after 21088 ms: Timed out

- fatal: unable to access 'https://github.com/kuukie-kq/HodgePodge.git/': OpenSSL SSL_read: Connection was reset, errno 10054

- error: RPC failed; curl 28 OpenSSL SSL_read: Connection was reset, errno 10054 fatal: expected flush

****

以上三种报错都与网络有关，首先通过浏览器看看是否为不可访问，如果没有问题则跟本地环境配置有关
有ssl校验和http代理等影响，主要修改$HOME/.gitconfig文件

****

- error: RPC failed; curl 18 transfer closed with outstanding read data remaining

- error: 2717 bytes of body are still expected

- fetch-pack: unexpected disconnect while reading sideband packet

- fatal: early EOF

- fatal: fetch-pack: invalid index-pack output

或者

- error: RPC failed; curl 56 OpenSSL SSL_read: SSL_ERROR_SYSCALL, errno 0

- error: 5711 bytes of body are still expected

- fetch-pack: unexpected disconnect while reading sideband packet

- fatal: early EOF

- fatal: fetch-pack: invalid index-pack output

****

这两种报错网上（包括chatgpt的答案）有缓冲区太小问题（curl相关甚至存在为0的情况）有网络连接相关问题
有仓库权限未开放问题（gpt）git本身的版本问题多种可能
一一尝试排除后都不是根本原因
根据commit记录仔细检查回忆之前clone的记录后并通过新建仓库测试发现是因为live2d资源文件（ps生成的）产生影响
既HodgePodge/CYpackage/ELF/static/live2d/model（HodgePodge/CYpackage/PetLive2D/static/live2d/model）目录下的文件

``` shell
git config --global http.version HTTP/1.1
git clone --depth=1 https://github.com/kuukie-kq/HodgePodge e:/GitHub/kuukie-kq/HodgePodge
git fetch --unshallow

# clone手动步骤解析
# 对当前文件夹初始化
git init
git remote add origin https://github.com/kuukie-kq/HodgePodge
git fetch --depth=1
```

- .gitconfig

``` conf
[http]
    version = HTTP/1.1
[user]
    email = 3260681415@qq.com
    name = kuukie

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
