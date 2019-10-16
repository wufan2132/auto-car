# auto-car

config:   配置文件目录

data：   rosbag包、core、log等文件目录

docker:   docker相关脚本以及镜像包目录

docs：相关文档

file：相关文件（比如地图）

launch： roslaunch脚本

scripts：常用脚本文件

src：模块代码

user：个人文件夹，不受git版本管理，可以存放一些其他需要在docker下 测试的代码，以及不需要安装的程序包。也可以用作本地主机与docker文件交互的中转。

devel\build：编译生成的文件

一、环境安装：

    本地主机运行 ./set_up.sh

二、编译环境：

    1、安装完成后进入docker

        ./docker/scripts/dev_into.sh
        
    2、编译

        ./build.sh

三、运行

        ./run.sh

四、了解更多指令用途可以运行

        ./xxx.sh --help （有些指令的帮助文档还没写完）

五、其他

        docker 相关：docker/README.md



