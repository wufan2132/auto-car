#include "planning/planning.h"

Car_Planning::Car_Planning(YAML::Node planning_conf){
    conf.mode = planning_conf["mode"].as<string>();
    conf.period = planning_conf["period"].as<float>();
    conf.trajectory_dir = planning_conf["trajectory_dir"].as<string>();
    conf.sampling_period = planning_conf["sampling_period"].as<int>();
    optimizer = new path_optimizer(planning_conf["path_optimizer_conf"]);
}


void Car_Planning::RunOnce(void){
    //origin_path to this_path
}

//读节点数据
void Car_Planning::localization_callback(const car_msgs::localization& localization){
    car_localization = localization;
}

void Car_Planning::chassis_callback(const car_msgs::chassis& chassis){
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
//
void Car_Planning::OnTimer(const ros::TimerEvent&){
    if(refrence_Trajectory.total_path_length==0){
        // 读取轨迹
        static replay replayer(conf.trajectory_dir,"read");
        load_trajectory_from_replay(replayer, origin_Trajectory);
        // 轨迹处理 
        refrenceline_Sp = optimizer->get_refrenceline(origin_Trajectory, refrence_Trajectory);
        refrenceline_publisher.publish(refrence_Trajectory);
    }
    //坐标系转换
    Coordinate_converter::POS_to_SL(refrence_Trajectory,car_status,car_status_sl);
    //
    optimizer->process(car_status_sl,refrenceline_Sp,now_Trajectory);
    //cout << "now_Trajectory:"<<now_Trajectory.total_path_length<<endl;
    //cout<<"publish:"<<now_Trajectory.trajectory_path.size()<<endl;
    //发布
    trajectory_publisher.publish(now_Trajectory);
}