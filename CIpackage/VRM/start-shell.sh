docker images
docker run --net host -d redis:6 redis-server --appendonly yes
docker run -itd --net host -e MYSQL_ROOT_PASSWORD=root mysql:8.0
docker run --net host vrm:v1

