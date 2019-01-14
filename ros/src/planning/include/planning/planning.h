#pragma once


#include "planning/common.h"
#include "planning/replay.h"
#include "planning/car_model.h"
#include "planning/Interpolating.h"
#include "planning/path_optimizer.h"
#include "planning/refrenceline.h"
#include "planning/planner/og_planner.h"
#include "planning/planner/sp_planner.h"
#include "planning/planner/mp_planner.h"
#include "planning/planner/test_planner.h"
#include "planning/obstacle/obstacle_list.h"
#include "planning/debugger/debugger.h"
#include <Eigen/Dense>
#include "stdlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Car_Planning_Conf{
public:
    string mode;
    double period;
    string refrenceline_source;
    double wait_time;
    string trajectory_dir;
    int sampling_period;
};

class Car_Planning{
    public:
        Car_Planning(YAML::Node yaml_conf);

        void Init();

        void RunOnce(void);

        void OnTimer(const ros::TimerEvent&);

        void localization_callback(const car_msgs::localization& localization);

        void chassis_callback(const car_msgs::chassis& chassis);

        void obstacle_callback(const car_msgs::base_obstacle_list& obstacle_msg);

        car_msgs::trajectory_point generate_trajectory_point(const car_msgs::localization& localization,
                                                                const car_msgs::chassis& chassis);
    //标志位
    bool STATE;
    //接收状态缓存
    car_msgs::localization car_localization;
    car_msgs::chassis car_chassis;
    //car 状态
    car_msgs::trajectory_point car_status;
    Car_State_SL car_status_sl;
    //refrenceline 解析形式
    Spline_Out* refrenceline_Sp;
    //各种轨迹
    car_msgs::trajectory origin_Trajectory;
    car_msgs::trajectory refrence_Trajectory;
    car_msgs::trajectory now_Trajectory;

    //ros通信模块
    ros::Subscriber localization_subscriber;
    ros::Subscriber chassis_subscriber;
    ros::Subscriber obstacle_subscriber;
    ros::Publisher trajectory_publisher;
    ros::Publisher refrenceline_publisher;
    //配置参数
    Car_Planning_Conf conf;
    //模块
    Planner* planner;
    Refrenceline_provider* rprovider;
    ObstacleList* obstaclelist;
};

/*path_point*/
// Header header
// geometry_msgs/Point position
// float64 speed
// float64 accel
// float64 yaw
// float64 curva
// float64 s
// float64 time
/*position*/
// float64 x
// float64 y
// float64 z
