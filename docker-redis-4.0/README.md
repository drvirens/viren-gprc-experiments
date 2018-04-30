

<code>
    docker build -t tag_redis_v_4_0 .

    ➜  docker-redis-4.0 git:(master) ✗ docker image ls

REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE

nginx_v_1_13_12     latest              ab511d478668        3 hours ago         67.2MB
redis               latest              c5355f8853e4        4 weeks ago         107MB
tag_redis_v_4_0     latest              c5355f8853e4        4 weeks ago         107MB
alpine              3.7                 3fd9065eaf02        3 months ago        4.15MB


    docker run -d -p 6379:6379 --name name_redis_v_4_0 c5355f8853e4
</code>