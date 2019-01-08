#include "planning/trajectory_generation.h"

#define pi 3.14159265354

bool TrajectoryGeneration::getTrajectory_from_SLT(const MatrixXf& S,const MatrixXf& L,const VectorXf& T,
                            const Spline_Out* refrenceline_Sp,
                            car_msgs::trajectory& trajectory_now,
                            int start_index){
    int len = T.rows();
    // cout<<"getTrajectory_from_SLT:"<<endl;
    // cout<<"T:"<<endl;
    // cout<<T<<endl;
    // cout<<"start_index:"<<start_index<<endl;
    trajectory_now.trajectory_path.resize(start_index + len);
    for(int i=0;i<len;i++){
        trajectory_now.trajectory_path[start_index+i].s = S(i,0);
        trajectory_now.trajectory_path[start_index+i].speed = S(i,1);
        trajectory_now.trajectory_path[start_index+i].accel = S(i,2);
        //debug
        // cout<<"i:"<<i+1
        // <<"   s:"<<trajectory_now.trajectory_path[start_index+i].s
        // <<"   speed:"<<trajectory_now.trajectory_path[start_index+i].speed
        // <<"   acc"<<trajectory_now.trajectory_path[start_index+i].accel<<endl;
    }
    //cout<<"start_sl.s:"<<start_sl.s<<"  s0:"<<trajectory_now.trajectory_path[0].s<<endl;
    //cout<<"POS TO SL:"<<endl;
    for(int i=0;i<len;i++){
        //SL to POS
        Coordinate_converter::SL_to_POS(trajectory_now.trajectory_path[start_index+i].s, L(i,0),
                refrenceline_Sp->sx,refrenceline_Sp->sy,trajectory_now.trajectory_path[start_index+i]);
            
        trajectory_now.trajectory_path[start_index+i].relative_time = T(i);
        trajectory_now.trajectory_path[start_index+i].header.seq = start_index+i+1;
        //debug
        if(i>0&&  
        (abs(trajectory_now.trajectory_path[start_index+i-1].x-trajectory_now.trajectory_path[start_index+i].x)>10
        ||abs(trajectory_now.trajectory_path[start_index+i-1].y-trajectory_now.trajectory_path[start_index+i].y)>10)){
            ROS_INFO("pos error!"); 
        }
        // cout
        // <<trajectory_now.trajectory_path[start_index+i].header.seq<<","
        // <<trajectory_now.trajectory_path[start_index+i].x<<","
        // <<trajectory_now.trajectory_path[start_index+i].y<<","
        // <<pos<<","
        // <<trajectory_now.trajectory_path[start_index+i].s<<","
        // <<L(i,0)<<","
        // <<refrenceline_x<<","
        // <<refrenceline_y<<","
        // <<refrenceline_theta<<endl;
    }
    //计算theta
    float dx,dy;
    for(int i=0;i<len-1;i++){
        dx = trajectory_now.trajectory_path[start_index+i+1].x - trajectory_now.trajectory_path[start_index+i].x;
        dy = trajectory_now.trajectory_path[start_index+i+1].y - trajectory_now.trajectory_path[start_index+i].y;
        trajectory_now.trajectory_path[start_index+i].theta = Interpolating::yaw(dx,dy);
        //debug
        //ROS_INFO("dx:%f dy:%f theta:%f", dx,dy,trajectory_now.trajectory_path[start_index+i].theta);
        if(i>1&&i<len-2&&abs(trajectory_now.trajectory_path[start_index+i-1].theta-trajectory_now.trajectory_path[start_index+i].theta)>0.5&&
        abs(trajectory_now.trajectory_path[start_index+i-1].theta-trajectory_now.trajectory_path[start_index+i].theta)<pi){
            dx = trajectory_now.trajectory_path[start_index+i+2].x - trajectory_now.trajectory_path[start_index+i-1].x;
            dy = trajectory_now.trajectory_path[start_index+i+2].y - trajectory_now.trajectory_path[start_index+i-1].y;
            trajectory_now.trajectory_path[start_index+i].theta = Interpolating::yaw(dx,dy);
        //ROS_INFO("dx:%f dy:%f theta:%f  changed!", dx,dy,trajectory_now.trajectory_path[start_index+i].theta);
        }
    }
    //优化theta
    trajectory_now.trajectory_path[start_index + len-1].theta = 2*trajectory_now.trajectory_path[start_index+len-2].theta - trajectory_now.trajectory_path[start_index+len-3].theta;

    // //使用多项式拟合
    // VectorXf thetaVec(len);
    // for(int i=0;i<len;i++) 
    //     thetaVec(i) = trajectory_now.trajectory_path[start_index+i].theta;
    // Fitting::gradient_descent_optimizer(thetaVec);
    // //debug
    // for(int i=0;i<len;i++)
    //     ROS_INFO("%d, theta0:%8.6f theta1:%8.6f",i+1, trajectory_now.trajectory_path[start_index+i].theta, thetaVec(i)); 
    // //
    // for(int i=0;i<len;i++) 
    //     trajectory_now.trajectory_path[start_index+i].theta = thetaVec(i);
    
    //计算曲率
    for(int i=0;i<len-1;i++){
        dx = trajectory_now.trajectory_path[start_index+i+1].x - trajectory_now.trajectory_path[start_index+i].x;
        dy = trajectory_now.trajectory_path[start_index+i+1].y - trajectory_now.trajectory_path[start_index+i].y;
        float dtheta = trajectory_now.trajectory_path[start_index+i+1].theta - trajectory_now.trajectory_path[start_index+i].theta;
        if(dtheta>pi) dtheta = dtheta - 2*pi;
        if(dtheta<-pi) dtheta = dtheta + 2*pi;
        if(dx==0&&dy==0)
            trajectory_now.trajectory_path[start_index+i].kappa = 0;
        else
            trajectory_now.trajectory_path[start_index+i].kappa = dtheta/sqrt(dx*dx+dy*dy);
        
    }
    //去掉最后一个不可用点
    trajectory_now.trajectory_path.pop_back();

    trajectory_now.total_path_length = trajectory_now.trajectory_path.size();
    trajectory_now.total_path_time = T(len-1);
    trajectory_now.absolute_time = ros::Time::now().toSec();
}