
#cInstructions:

<br>

## source: https://stackify.com/docker-tutorial/

<code>
<br>


docker build -t virennginx11312 .

<br>

docker image ls

<br>

docker run --name vs-nginx-1.13.12 -p 8080:80 virennginx11312


<br>

</code>

test:
<br>
http://127.0.0.1:8080



<br>
<br>


<code>

    

    docker rm name_nginx_v_1_13_12 

    

    docker rmi nginx_v_1_13_12

    

    docker build -t nginx_v_1_13_12 .

    

    docker run --name name_nginx_v_1_13_12 -p 80:80 nginx_v_1_13_12

    

</code>


    <br>
    ➜  docker-nginx-v1.13.12 git:(master) ✗ docker run --name name_nginx_v_1_13_12 -p 80:80 nginx_v_1_13_12
    <br>
172.17.0.1 - - [30/Apr/2018:06:08:03 +0000] "POST /route.VSStoreDB/Store HTTP/2.0" 200 73 "-" "grpc-c++/1.11.0 grpc-c/6.0.0 (osx; chttp2; gorgeous)"

