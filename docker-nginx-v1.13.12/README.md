
Instructions:

<br>

# source: https://stackify.com/docker-tutorial/


<br>


docker build -t virennginx11312 .

<br>

docker image ls

<br>

docker run --name vs-nginx-1.13.12 -p 8080:80 virennginx11312


<br>

test:
<br>
http://127.0.0.1:8080