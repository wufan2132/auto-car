docker一般包括两层：
image(镜像层)
container(容器层)
容器层是建立在镜像层之上的一个类似于虚拟机的东西。
你的电脑可能会同时存在多个images和containers

1. 创建docker
1）从.tar文件创建一个新的镜像，在根据这镜像创建一个docker容器
注意：创建新docker建议先执行docker/scripts/docker_clean.sh 关闭所有的容器，删除所有镜像。
直接执行./set_up.sh，保证docker/images/路径下有正确的.tar 镜像文件。

2) 直接从现有镜像创建一个docker容器
docker images查看对应的镜像tag
./docker/scripts/dev_start.sh  -t [tag]
或者直接使用默认的第一个镜像
./docker/scripts/dev_start.sh

2. 使用docker
创建完docker后，docker会默认开启。直接使用 ：./docker/scripts/dev_into.sh 进入docker即可。
重启电脑后，docker是不会自动开启的，如果想使用之前创建的docker容器，输入：
docker start autocar_dev 开启名为autocar_dev的容器
再进入docker即可。

3. 其他
docker ps 查看正在运行的容器
docker stop autocar_dev 关闭某个正在运行的容器