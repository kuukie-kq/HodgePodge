# Docker image for VRMspringbootweb file run
# version 1.0.0

# pull base image
from java:8
# listen port
expose 20022
# producer
maintainer kuukie <3260681415@qq.com>
# disploy project
add VRM.tar /kuukie/
# workspace
workdir /kuukie/VRM-VirtualRouter
# main java jar
# copy SpringBootWeb-1.0-SNAPSHOT.jar /opt/kuukie/
# main run
entrypoint ["java","-jar","/kuukie/VRM-VirtualRouter/SpringBootWeb/target/SpringBootWeb-1.0-SNAPSHOT.jar"]






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
