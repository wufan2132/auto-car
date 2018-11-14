#include "planning/planning.h"


Car_Planning::Car_Planning(YAML::Node planning_conf){
    conf.mode = planning_conf["mode"].as<string>();
    conf.trajectory_dir = planning_conf["trajectory_dir"].as<string>();
    optimizer = new path_optimizer(planning_conf["path_optimizer"]);
}


void Car_Planning::RunOnce(void){
    //origin_path to this_path
}

//读节点数据
void Car_Planning::localization_callback(const car_msgs::localization& localization){
    car_localization = localization;
}

void Car_Planning::chassis_callback(const car_msgs::chassis& chassis){
    static replay replayer(conf.trajectory_dir,"write");
    static int count = 0;
    count++;
    //cout<<"chassis callback"<<endl;
    car_chassis = chassis;
    if(count>100&&car_localization.header.seq>0){
        count=0;
        replayer.saveOnce(generate_trajectory_point(car_localization, car_chassis));
    }
}

car_msgs::trajectory_point Car_Planning::generate_trajectory_point(const car_msgs::localization& localization,const car_msgs::chassis& chassis){
    car_msgs::trajectory_point point;
    //生成 point
    point.x = localization.position.x;
    point.y = localization.position.y;
    point.z = localization.position.z;
    point.theta = localization.angle.z;
    cout<<"x:"<<point.x<<"  y:"<<point.y<<endl;
    return point;
}

void Car_Planning::load_trajectory_from_replay(replay& replayer){
    static int count=0;
    
    replayer.reset();       
    origin_Trajectory.header.seq = count; 
    origin_Trajectory.trajectory_path.clear();
    car_msgs::trajectory_point point;
    while(replayer.readOnce(point))
    {
        origin_Trajectory.trajectory_path.push_back(point);
    }
    origin_Trajectory.total_path_length = origin_Trajectory.trajectory_path.size();
    //cout<<"get "<<origin_Trajectory.total_path_length<<" point."<<endl;
    count++;
}
//
void Car_Planning::OnTimer(const ros::TimerEvent&){
    // 读取轨迹
    static replay replayer(conf.trajectory_dir,"read");
    load_trajectory_from_replay(replayer);
    //轨迹处理 
    optimizer->process(origin_Trajectory, now_Trajectory);
    //cout<<"publish:"<<now_Trajectory.trajectory_path.size()<<endl;
    //发布
    trajectory_publisher.publish(now_Trajectory);
}