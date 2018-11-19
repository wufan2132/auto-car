#include "planning/path_optimizer.h"

#define pi 3.14159265354
path_optimizer::path_optimizer(YAML::Node optimizer_conf){
    conf.step_t     = optimizer_conf["step_t"].as<float>();
    conf.planning_t = optimizer_conf["planning_t"].as<float>();
    conf.aim_speed  = optimizer_conf["aim_speed"].as<float>();
    interpolating = new Interpolating(optimizer_conf["Interpolating_conf"]);
}


Spline_Out* path_optimizer::get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out){
    return interpolating->process(trajectory_in, trajectory_out);
}

 void path_optimizer::get_sampling_line(const Car_State_SL& status_sl, const car_msgs::trajectory& refrenceline, car_msgs::trajectory& trajectory_out){
    //速度规划
    VectorXf QP4(5);
    QP4 = Fitting::quartic4_polynomial(status_sl.s, status_sl.sv, status_sl.sa, conf.aim_speed, 0 , conf.planning_t);
    int len = conf.planning_t/conf.step_t+1;
	VectorXf T = VectorXf::LinSpaced(len, 0, conf.planning_t);
    MatrixXf S_out;
    Fitting::cal_point_quartic4(QP4,T,S_out);
    //转换
    if(len<5)
        cout << "sample error!"<<endl;
    trajectory_out.trajectory_path.resize(len);
    for(int i=0;i<len;i++){
        trajectory_out.trajectory_path[i].s = S_out(i,0);
        trajectory_out.trajectory_path[i].speed = S_out(i,1);
        trajectory_out.trajectory_path[i].accel = S_out(i,2);
    }
    //cout<<"status_sl.s:"<<status_sl.s<<"  s0:"<<trajectory_out.trajectory_path[0].s<<endl;
    //横向位置规划
    VectorXf QP5(6);
    QP5 = Fitting::quintic5_polynomial(status_sl.h,status_sl.dh,status_sl.ddh,0,0,0,trajectory_out.trajectory_path.back().s-status_sl.s);
    VectorXf S;
    S.resizeLike(S_out.col(0));
    for(int i=0;i<S.rows();i++){
        S(i) = S_out(i,0) - status_sl.s;
    }
    MatrixXf L_out;
    Fitting::cal_point_quintic5(QP5 ,S,L_out);
    for(int i=0;i<len;i++){
        float refrenceline_x,refrenceline_y,refrenceline_theta;
        if(i==0)
            get_pos_in_refrenceline(refrenceline,trajectory_out.trajectory_path[i].s,refrenceline_x,refrenceline_y,refrenceline_theta,status_sl.index);
        else
            get_pos_in_refrenceline(refrenceline,trajectory_out.trajectory_path[i].s,refrenceline_x,refrenceline_y,refrenceline_theta);
        trajectory_out.trajectory_path[i].x = refrenceline_x - L_out(i,0)*sin(refrenceline_theta);
        trajectory_out.trajectory_path[i].y = refrenceline_y + L_out(i,0)*cos(refrenceline_theta);
        trajectory_out.trajectory_path[i].z = 0;
        trajectory_out.trajectory_path[i].relative_time = T(i);
        trajectory_out.trajectory_path[i].header.seq = i+1;
        if(i==0)
        //输出info
            ROS_INFO("x:%f  y:%f  theta:%f  L:%f  rx:%f  ry:%f", trajectory_out.trajectory_path[i].x,trajectory_out.trajectory_path[i].y
            ,refrenceline_theta, L_out(i,0), refrenceline_x, refrenceline_y);
    }
   
    //计算其他
    float dx,dy;
    for(int i=0;i<len-1;i++){
        dx = trajectory_out.trajectory_path[i+1].x - trajectory_out.trajectory_path[i].x;
        dy = trajectory_out.trajectory_path[i+1].y - trajectory_out.trajectory_path[i].y;
        trajectory_out.trajectory_path[i].theta = Interpolating::yaw(dx,dy);
    }
    trajectory_out.trajectory_path[len-1].theta = 2*trajectory_out.trajectory_path[len-2].theta - trajectory_out.trajectory_path[len-3].theta;
    for(int i=0;i<len-1;i++){
        dx = trajectory_out.trajectory_path[i+1].x - trajectory_out.trajectory_path[i].x;
        dy = trajectory_out.trajectory_path[i+1].y - trajectory_out.trajectory_path[i].y;
        trajectory_out.trajectory_path[i].kappa = (trajectory_out.trajectory_path[i+1].theta - trajectory_out.trajectory_path[i].theta)/sqrt(dx*dx+dy*dy);
    }
    trajectory_out.total_path_length = len;
    trajectory_out.total_path_time = conf.planning_t;
 }


void path_optimizer::process(const Car_State_SL& status_sl, const car_msgs::trajectory& refrenceline, car_msgs::trajectory& trajectory_out){
    static int count = 0;
    count++;
    get_sampling_line(status_sl, refrenceline, trajectory_out);
    //添加header
    trajectory_out.header.seq = count;
}

void path_optimizer::get_pos_in_refrenceline(const car_msgs::trajectory& refrenceline, float s,
     float& refrenceline_x, float& refrenceline_y,float& refrenceline_theta, int start_index){
   	static int pos = start_index;
    int len = refrenceline.trajectory_path.size();
    if (s < 0) pos = start_index;
	else if (start_index!=-1)
	{
		pos = start_index;
	}else if (s >= refrenceline.trajectory_path[len - 1].s){
        pos = len - 2;
    }else{
        while (s >= refrenceline.trajectory_path[pos].s) pos++;
    }
    float k = (s - refrenceline.trajectory_path[pos].s)/(refrenceline.trajectory_path[pos+1].s - refrenceline.trajectory_path[pos].s);
    refrenceline_x = refrenceline.trajectory_path[pos].x + k*(refrenceline.trajectory_path[pos+1].x - refrenceline.trajectory_path[pos].x);
    refrenceline_y = refrenceline.trajectory_path[pos].y + k*(refrenceline.trajectory_path[pos+1].y - refrenceline.trajectory_path[pos].y);
    refrenceline_theta = (refrenceline.trajectory_path[pos].theta + refrenceline.trajectory_path[pos+1].theta)/2;
    
	return; 
}