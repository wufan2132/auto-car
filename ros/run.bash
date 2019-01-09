#!/bin/bash 

#添加或修改 /etc/hosts中的ip
#192.168.1.132 pc                                                                                     
#192.168.1.110 tx2

if [[ "X$1" == "X" || "X$2" == "X" ]];then
    local_name="pc"
    master_name="pc"
else
    local_name="$1"
    master_name="$2"
fi
echo "local:$local_name , master:$master_name"

export ROS_HOSTNAME=$local_name
export ROS_MASTER_URI=http://$master_name:11311

source devel/setup.bash

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
