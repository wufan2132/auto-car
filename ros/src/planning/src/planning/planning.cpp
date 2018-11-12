#include "planning/planning.h"


void Car_Planning::Init(void){
}

void Car_Planning::RunOnce(void){
    //origin_path to this_path
}

void Car_Planning::Get_path(const car_msgs::trajectory& path){
    //origin_Trajectory = path;
}


//读节点数据
void Car_Planning::localization_callback(const car_msgs::localization& localization){
    car_localization = localization;
}

void Car_Planning::chassis_callback(const car_msgs::chassis& chassis){
    static replay replayer("trajectory.csv","write");
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

//
void Car_Planning::OnTimer(const ros::TimerEvent&){
    //读取轨迹
    static replay replayer("trajectory.csv","read");
    load_trajectory_from_replay(replayer);
    //轨迹处理 
    Eigen::VectorXf xVec(int(origin_Trajectory.total_path_length));
    Eigen::VectorXf yVec(int(origin_Trajectory.total_path_length));
    for(int i=0;i<origin_Trajectory.trajectory_path.size();i++)
    {
        xVec(i) = origin_Trajectory.trajectory_path[i].x;
        yVec(i) = origin_Trajectory.trajectory_path[i].y;
    }
    Spline_Out csp;
    // cout<<"Spline2D"<<endl;
    Interpolating::Spline2D(xVec, yVec, csp);
    now_Trajectory.header = origin_Trajectory.header;
    now_Trajectory.total_path_length = csp.length;
    now_Trajectory.trajectory_path.clear();
    for(int i=0;i<csp.length;i++)
    {
        car_msgs::trajectory_point point;
        point.header.seq = i;
        point.x = csp.x(i);
        point.y = csp.y(i);
        point.s = csp.s(i);
        point.theta = csp.yaw(i);
        point.kappa = csp.curvature(i);
        now_Trajectory.trajectory_path.push_back(point);
    }
    cout<<"publish:"<<now_Trajectory.trajectory_path.size()<<endl;
    //发布
    trajectory_publisher.publish(now_Trajectory);
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
    cout<<"get "<<origin_Trajectory.total_path_length<<" point."<<endl;
    count++;
}