# source: https://stackify.com/docker-tutorial/

docker build -t virennginx11312 .
docker image ls
docker run --name vs-nginx-1.13.12 -p 8080:80 virennginx11312


http://127.0.0.1:8080