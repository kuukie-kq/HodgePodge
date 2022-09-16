# Docker image make file
# Created by kuu-kie on 2022/03/15
# version 1.1.1

# pull base image 根据java1.8镜像制作项目镜像
from java:8
# listen port 对外开放端口
expose 20022
# producer kuukie 作者信息
maintainer kuukie <3260681415@qq.com>
# disploy project 项目包
add VRM.tar /kuukie/
# workspace 项目主目录
workdir /kuukie/VRM-VirtualRouter
# main run 镜像启动默认程序
entrypoint ["java","-jar","/kuukie/VRM-VirtualRouter/SpringBootWeb/target/SpringBootWeb-1.0-SNAPSHOT.jar"]

# other command 其他指令及用处
# # 与entrypoint类似，执行命令，一般用于创建镜像时为镜像定制特定环境
# run
# # 与add类似，拷贝文件到镜像中，与add区别在于add可以自动对tar包进行解包（环境能解的情况），路径不存在会自动创建
# copy
# # 与runentrypoint类似，执行命令，run触发是在build，cmd和entrypoint触发是在run，entrypoint一般不会被run命令覆盖，两个配合使用一般用于run时的变参，entrypoint为固定部分，cmd为可变参数的默认值
# cmd
# # 定义环境变量
# env
# # 与env类型，都是定义变量，但是arg的作用域只针对Dockerfile，构建好的镜像时没有这个变量的
# arg
# # 定义匿名的数据卷，主要防止容器不断变大和重要数据丢失
# volume
# # 用于指定后续命令的用户与组，仅切换
# user
# # 指定程序监控容器的运行状态
# healthcheck
# # 延迟构建命令的执行，在其他Dockerfile使用from时，构建的时候执行
# onbuild
# # 为镜像添加元数据
# label
# 总结，基本都知道做什么用的，但是因为环境问题，需要不断的尝试才知道到底成没成功。比如我的tar包原本是zip格式，后来尝试tar.gz都不行，甚至尝试apt install gzip unzip也不行。
# 如下是一些docker常用命令


#$sudo docker images
#$sudo docker build -t vrm:v1 .
#$sudo docker run -p 8088:20022 vrm:v1
#$sudo docker ps -a
#$sudo docker exec -it *** /bin/bash
#$sudo docker run -d -p 8088:20022 vrm:v1
#$sudo docker rm $(sudo docker ps -a -q)
#$sudo docker stop $(sudo docker ps -q)

#$sudo docker run -p 6379:6379 -d redis:6 redis-server --appendonly yes
#$sudo docker run -itd -p 3306:3306 -e MYSQL_ROOT_PASSWORD=root mysql:8.0
#$sudo docker cp ./virtual_router_db.sql ID(mysql:8.0):/opt/
#$docker$mysql>source /opt/virtual_router_db.sql;
#$docker$mysql>grant all privileges on *.* to 'root'@'%' with grant option;
#$docker$mysql>flush privileges;
