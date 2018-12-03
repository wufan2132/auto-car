#!/bin/bash 

#添加或修改 /etc/hosts中的ip
#192.168.1.132 pc                                                                                     
#192.168.1.110 tx2

if [[ "X$1" == "X" ]];then
    echo "please run: ./run.bash <1> <2> <3>"
    source devel/setup.bash
    exit 0
elif [[ "X$1" != "X" && "X$2" != "X" && "X$3" == "X" ]];then
    local_name="$1"
    master_name="$2"
    export ROS_HOSTNAME=$local_name
    export ROS_MASTER_URI=http://$master_name:11311
    source devel/setup.bash
elif [[ "X$1" != "X" && "X$2" != "X" && "X$3" == "Xr" ]];then #pc上单独运行 用于bag play
    local_name="$1"
    master_name="$2"
    source devel/setup.bash
elif [[ "X$1" != "X" && "X$2" != "X" && "X$3" == "Xs" ]];then
    local_name="$1"
    master_name="$2"
    export ROS_HOSTNAME=$local_name
    export ROS_MASTER_URI=http://$master_name:11311
    source devel/setup.bash
    echo "ROS_HOSTNAME=$local_name, ROS_MASTER_URI=http://$master_name:11311 , source devel/setup.bash"
    exit 0
else
    echo "error! please run:
    ./run.bash pc pc
    ./run.bash pc pc s
    ./run.bash tx tx
    ./run.bash tx tx s
    ./run.bash pc tx
    ./run.bash pc tx s
    ./run.bash pc tx r"
    exit 0
fi

echo "local:$local_name , master:$master_name"

if [[ "$local_name" == "pc" && "$master_name" == "pc" ]];then
    echo "running on pc"
    roslaunch launch/auto-car-pc.launch
elif [[ "$local_name" == 'pc' && "$master_name" == 'tx2' ]];then
    echo "running on pc for tx2"
    roslaunch launch/auto-car-pc-for-tx2.launch
elif [[ "$local_name" == 'tx2' && "$master_name" == 'tx2' ]];then
    echo "running on tx2"
    roslaunch launch/auto-car-tx2.launch
fi
