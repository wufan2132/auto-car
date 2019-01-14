#include "planning/planning.h"
//
//const string PLANNER_CONF_DIR = 
//   "../my-code/auto-car/ros/src/planning/conf/sp_planner_conf.yaml";
// const string PLANNER_CONF_DIR = 
//     "../my-code/auto-car/ros/src/planning/conf/og_planner_conf.yaml";



Car_Planning::Car_Planning(YAML::Node planning_conf)
:STATE(0)
{
    conf.mode = planning_conf["mode"].as<string>();
    conf.refrenceline_source = planning_conf["refrenceline_source"].as<string>();
    conf.period = planning_conf["period"].as<double>();
    conf.wait_time = planning_conf["wait_time"].as<double>();
    conf.trajectory_dir = 
        Common::convert_to_debugpath(planning_conf["trajectory_dir"].as<string>());
    conf.sampling_period = planning_conf["sampling_period"].as<int>();
    /***************模块初始化*************************/
    rprovider = new Refrenceline_provider(planning_conf["refrenceline_provider"]);
    obstaclelist = new ObstacleList(planning_conf["obstacle_list"]);
    //规划器初始化
    string planner_name = planning_conf["planner"].as<string>();
    string planner_path =
        Common::convert_to_debugpath(planning_conf["planner_dir"].as<string>());
    if(planner_name=="OgPlanner")
        planner = new OgPlanner(YAML::LoadFile(planner_path+planner_name+"_conf.yaml"));
    else if(planner_name=="SpPlanner")
        planner = new SpPlanner(YAML::LoadFile(planner_path+planner_name+"_conf.yaml"));
    else if(planner_name=="MpPlanner")
        planner = new MpPlanner(YAML::LoadFile(planner_path+planner_name+"_conf.yaml"));
    else if(planner_name=="TestPlanner")
        planner = new TestPlanner(YAML::LoadFile(planner_path+planner_name+"_conf.yaml"));
    else
        ROS_ERROR("Car_Planning::Car_Planning: invalid planner name!");
}


void Car_Planning::RunOnce(void){
    //origin_path to this_path
}

//读节点数据
void Car_Planning::localization_callback(const car_msgs::localization& localization){
    car_localization = localization;
}

void Car_Planning::chassis_callback(const car_msgs::chassis& chassis){
    if(STATE==0)
        STATE=1;
    car_chassis = chassis;
    car_status = generate_trajectory_point(car_localization, car_chassis);
    //cout<< "chassis_callback"<<endl;
    if(conf.mode=="write"){
        static replay replayer(conf.trajectory_dir,"write");
        //cout<<"chassis callback"<<endl;
        if(car_localization.header.seq>0){
            replayer.saveOnce(car_status,conf.sampling_period);
        }
    }
}

void Car_Planning::obstacle_callback(const car_msgs::base_obstacle_list& obstacle_msg){
    obstaclelist->refresh(obstacle_msg);
}

car_msgs::trajectory_point Car_Planning::generate_trajectory_point(const car_msgs::localization& localization,const car_msgs::chassis& chassis){
    static int count=0;
    count++;
    car_msgs::trajectory_point point;
    //生成 point
    point.header.seq = count;
    point.x = localization.position.x;
    point.y = localization.position.y;
    point.z = localization.position.z;
    point.theta = localization.angle.z;
    point.speed = chassis.speed.x;
    point.accel = chassis.acc.x;
    return point;
}



//主要作用是发送参考线信息，并且等待传感器连接
void Car_Planning::Init(){
    /*检查是否连接上*/
    ros::Duration(1).sleep();
    double time_begin =ros::Time::now().toSec();
    double time_now = time_begin;
    while(STATE==1||conf.wait_time<0||time_now-time_begin>conf.wait_time){
        ros::Duration(0.5).sleep(); // sleep for half a second
        time_now =ros::Time::now().toSec();
    }
    if(time_now-time_begin>conf.wait_time){
        ROS_ERROR("Car_Planning::Init: Can not receive car message!");
        ros::shutdown();
    }
    /*发送参考线*/
    // 读取轨迹
    if(conf.refrenceline_source == "replay"){
        static replay replayer(conf.trajectory_dir,"read");
        replay::load_trajectory_from_replay(replayer, origin_Trajectory);
    }else if(conf.refrenceline_source == "refrenceline_provider"){
        rprovider->process(origin_Trajectory);
    }else
        ROS_ERROR("Car_Planning::Init: invalid refrenceline_source!");
    // 轨迹处理 
    refrenceline_Sp = planner->get_refrenceline(origin_Trajectory, refrence_Trajectory);
    refrenceline_publisher.publish(refrence_Trajectory);
    //cout<<"published : "<<refrence_Trajectory.total_path_length<<endl;

    /*起点检测*/
    //如果起点的位置与车起点位置差的过大（大于5m）
    if((refrence_Trajectory.trajectory_path[0].x-car_status.x)*(refrence_Trajectory.trajectory_path[0].x-car_status.x)+
    (refrence_Trajectory.trajectory_path[0].y-car_status.y)*(refrence_Trajectory.trajectory_path[0].y-car_status.y)>5)
        ROS_WARN("Car_Planning::Init: The car is too far away from the starting point!");

        /*模块初始化*/
    obstaclelist->init(&refrence_Trajectory ,&car_status, &car_status_sl);
    planner->init(obstaclelist);
    debugger->init(refrenceline_Sp);
    
}

void Car_Planning::OnTimer(const ros::TimerEvent&){
    //TODO: 从csv中读取暂时放在这儿
    obstaclelist->process();
    //坐标系转换
    Coordinate_converter::POS_to_SL(refrence_Trajectory,car_status,car_status_sl);
    //
    planner->process(car_status, car_status_sl, refrenceline_Sp,refrence_Trajectory, now_Trajectory);
    //cout << "now_Trajectory:"<<now_Trajectory.total_path_length<<endl;
    //cout<<"publish:"<<now_Trajectory.trajectory_path.size()<<endl;
    //发布
    trajectory_publisher.publish(now_Trajectory);
}