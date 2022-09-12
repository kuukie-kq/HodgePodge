docker stop $(sudo docker ps -q)
docker rm $(sudo docker ps -a -q)

