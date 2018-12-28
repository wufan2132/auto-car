#include "planning/planning.h"
//

const string PLANNER_CONF_DIR = 
    "../my-code/auto-car/ros/src/planning/conf/og_planner_conf.yaml";



Car_Planning::Car_Planning(YAML::Node planning_conf)
:STATE(0)
{
    conf.mode = planning_conf["mode"].as<string>();
    conf.period = planning_conf["period"].as<double>();
    conf.wait_time = planning_conf["wait_time"].as<double>();
    conf.trajectory_dir = planning_conf["trajectory_dir"].as<string>();
    conf.sampling_period = planning_conf["sampling_period"].as<int>();
    //planner = new SpPlanner(planning_conf["path_optimizer_conf"]);

    string path = Common::convert_to_debugpath(PLANNER_CONF_DIR);
    planner = new OgPlanner(YAML::LoadFile(path));
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

void Car_Planning::load_trajectory_from_replay(replay& replayer, car_msgs::trajectory& refrence_line){
    static int count=0;
    
    replayer.reset();       
    refrence_line.header.seq = count; 
    refrence_line.trajectory_path.clear();
    car_msgs::trajectory_point point;
    while(replayer.readOnce(point))
    {
        refrence_line.trajectory_path.push_back(point);
    }
    refrence_line.total_path_length = refrence_line.trajectory_path.size();
    //cout<<"get "<<origin_Trajectory.total_path_length<<" point."<<endl;
    count++;
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
    static replay replayer(conf.trajectory_dir,"read");
    load_trajectory_from_replay(replayer, origin_Trajectory);
    // 轨迹处理 
    refrenceline_Sp = planner->get_refrenceline(origin_Trajectory, refrence_Trajectory);
    refrenceline_publisher.publish(refrence_Trajectory);
    //cout<<"published : "<<refrence_Trajectory.total_path_length<<endl;

    /*起点检测*/
    //如果起点的位置与车起点位置差的过大（大于5m）
    if((refrence_Trajectory.trajectory_path[0].x-car_status.x)*(refrence_Trajectory.trajectory_path[0].x-car_status.x)+
    (refrence_Trajectory.trajectory_path[0].y-car_status.y)*(refrence_Trajectory.trajectory_path[0].y-car_status.y)>5)
        ROS_WARN("Car_Planning::Init: The car is too far away from the starting point!");
}

void Car_Planning::OnTimer(const ros::TimerEvent&){
    //判断规划的起始位置
    
    //坐标系转换
    Coordinate_converter::POS_to_SL(refrence_Trajectory,car_status,car_status_sl);
    //
    planner->process(car_status, car_status_sl, refrenceline_Sp,refrence_Trajectory, now_Trajectory);
    //cout << "now_Trajectory:"<<now_Trajectory.total_path_length<<endl;
    //cout<<"publish:"<<now_Trajectory.trajectory_path.size()<<endl;
    //发布
    trajectory_publisher.publish(now_Trajectory);
}