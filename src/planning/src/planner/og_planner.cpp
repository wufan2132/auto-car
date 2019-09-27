#include "planning/planner/og_planner.h"

OgPlanner::OgPlanner(YAML::Node yaml_conf)
:Planner(yaml_conf){
    conf.step_t = yaml_conf["step_t"].as<double>();
    conf.planning_t = yaml_conf["planning_t"].as<double>();
    conf.aim_speed  = yaml_conf["aim_speed"].as<double>();
    conf.keep_t  = yaml_conf["keep_t"].as<double>();
    conf.available_l = yaml_conf["available_l"].as<double>();
    conf.speed_correction = yaml_conf["speed_correction"].as<double>();
    conf.speed_min_limit = yaml_conf["speed_min_limit"].as<double>();
}

Car_State_SL OgPlanner::get_start_point(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl,
                                                const car_msgs::trajectory& reference_line,
                                                car_msgs::trajectory& trajectory_now){
    static bool replanning_flag = 0;
    /*********************************************/
    //重新从车的当前位置开始规划的条件
    //1.预测的时间为0，设定成这样
    //2.上次轨迹丢失
    //3.车体偏离预设轨迹较远
     if(conf.keep_t==0||trajectory_now.total_path_length<5||
            TrajectoryStitcher::replanningTrajectory(car_status, trajectory_now, conf.available_l)){
        //重置标志位
        replanning_flag = 1;
        //设置起点为车的当前坐标
        Car_State_SL start_sl = status_sl;
        start_sl.start_pos = 0;
        ROS_INFO("OgPlanner::get_start_point: replanning!");
        start_sl.t = 0;
        return start_sl;
     }
     else{
        int start_index=0;
        while(start_index<trajectory_now.total_path_length-1&&status_sl.s-trajectory_now.trajectory_path[start_index+1].s>0) start_index++;
        float T0 = trajectory_now.trajectory_path[start_index].relative_time;
        VectorXf T(1);
        
        //第一次运行时间是没有偏差的
        if(replanning_flag){
            T<<(T0 + conf.keep_t);
            replanning_flag = 0;
        }else
            //预测一秒后的，本来这里要加上1，但由于后面相对时间是从0开始算的，已经加了1，
            T<<T0;
        MatrixXf S_out;
        Fitting::cal_point_quartic4(QP4,T,S_out);
        VectorXf S(1);
        S(0) = S_out(0,0) - car_last_sl.s;
        MatrixXf L_out;
        Fitting::cal_point_quintic5(QP5 ,S,L_out);
        int end_index = start_index+8;
        while(end_index<trajectory_now.total_path_length-1&&S_out(0,0)-trajectory_now.trajectory_path[end_index].s>0) end_index++;
        int len1 = end_index - start_index;
        for(int i=0;i<len1;i++){
            trajectory_now.trajectory_path[i] = trajectory_now.trajectory_path[i+start_index];
            trajectory_now.trajectory_path[i].relative_time -=T0;
            trajectory_now.trajectory_path[i].header.seq = i+1;
        }
        //设置起点为end_index当前坐标
        Car_State_SL start_sl;
        // start_sl.start_pos = status_sl.index;
        // Coordinate_converter::POS_to_SL(reference_line,trajectory_now.trajectory_path[end_index],start_sl);
        start_sl.s = S_out(0,0);
        start_sl.sv = S_out(0,1);
        start_sl.sa = S_out(0,2);
        start_sl.l = L_out(0,0);
        start_sl.dl = L_out(0,1);
        start_sl.ddl = L_out(0,2);
        start_sl.start_pos = len1;
        start_sl.t = conf.keep_t;
        ////////////////////////////////////////////////
        // int end_index2 = start_index+8;
        // Car_State_SL start_sl2;
        // start_sl2.index = status_sl.index;
        // Coordinate_converter::POS_to_SL(reference_line,trajectory_now.trajectory_path[end_index2],start_sl2);
        // start_sl2.index = 8;
        // start_sl2.t = conf.keep_t;
        // start_sl2.dl = L_out(0,1);
        // start_sl2.ddl = L_out(0,2);
        // cout << "s1:" <<start_sl.s<<"  s2:"<<start_sl2.s<<endl;
        // cout << "l1:" <<start_sl.l<<"  l2:"<<start_sl2.l<<endl;
        // cout << "sv1:" <<start_sl.sv<<"  sv2:"<<start_sl2.sv<<endl;
        // cout << "sa1:" <<start_sl.sa<<"  sa2:"<<start_sl2.sa<<endl;
        // cout << "dl1:" <<start_sl.dl<<"  dl2:"<<start_sl2.dl<<endl;
        // cout << "ddl1:" <<start_sl.ddl<<"  ddl2:"<<start_sl2.ddl<<endl;

        // // cout<<"S_out"<<endl;
        // // cout<<S_out<<endl;
        // cout<<"car_S:"<<status_sl.s<<endl;
        // cout<<"start_S:"<<start_sl.s<<endl;
        // cout<<"start_pos:"<<start_index<<"  end_pos:"<<end_index<<"  len1:"<< start_sl.start_pos << endl;
        return start_sl;
     }
}

void OgPlanner::get_current_line(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl,
                                         const Spline_Out* refrenceline_Sp, const car_msgs::trajectory& reference_line,
                                         car_msgs::trajectory& trajectory_now){
    static bool replanning_flag = 0;
    /***************速度修正-测试版*******************/
    //设置终点，终点只给定目标速度，其余参数为0
    Car_State_SL end_sl;
    double max_kappa = 0;
    for(int i=0;i<trajectory_now.trajectory_path.size();i++)
        max_kappa = max(max_kappa, abs(trajectory_now.trajectory_path[i].kappa));
    max_kappa = conf.speed_correction * conf.aim_speed * max_kappa;
    //最多降到0.3
    end_sl.sv = max(conf.aim_speed*conf.speed_min_limit, conf.aim_speed - max_kappa);
    //cout<<"aim_speed: "<< end_sl.sv <<endl;
    /*********************************************/
    Car_State_SL start_sl = get_start_point(car_status,status_sl, reference_line,trajectory_now );

    // sampler->reset(start_sl);

    // sampler->getpointsSL();


    //
    path_planning(start_sl, end_sl, conf.planning_t-start_sl.t, refrenceline_Sp, trajectory_now);
    for(int i=start_sl.start_pos;i<trajectory_now.total_path_length;i++)
        trajectory_now.trajectory_path[i].relative_time +=start_sl.t;
    /************debug 1***********/
    // for(int i=0;i<len;i++)
    // cout<<
    // trajectory_now.trajectory_path[start_index+i].header.seq<<","<<
    // trajectory_now.trajectory_path[start_index+i].x<<","<<
    // trajectory_now.trajectory_path[start_index+i].y<<","<<
    // trajectory_now.trajectory_path[start_index+i].theta<<","<<
    // trajectory_now.trajectory_path[start_index+i].kappa<<endl;
    /************debug 2***********/
    for(int i=0;i<trajectory_now.total_path_length;i++)
    cout<<
    trajectory_now.trajectory_path[i].header.seq<<"."<<
    " s:"<<trajectory_now.trajectory_path[i].s<<
    " t:"<<trajectory_now.trajectory_path[i].relative_time<<
    " x:"<<trajectory_now.trajectory_path[i].x<<
    " y:"<<trajectory_now.trajectory_path[i].y<<","<<
    " theta:"<<trajectory_now.trajectory_path[i].theta<<","<<
    " kappa:"<<trajectory_now.trajectory_path[i].kappa<<endl;
    return;

 }

void OgPlanner::process(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl,
                                 const Spline_Out* refrenceline_Sp, const car_msgs::trajectory& reference_line,
                                 car_msgs::trajectory& trajectory_now){
    static int count = 0;
    count++;
    get_current_line(car_status, status_sl, refrenceline_Sp,reference_line,  trajectory_now);
    //添加header
    trajectory_now.header.seq = count;
    //保存车体参数
    car_last_sl = status_sl;
}

void OgPlanner::path_planning(const Car_State_SL& start_sl,const Car_State_SL& end_sl,const float planning_t,
 const Spline_Out* refrenceline_Sp, car_msgs::trajectory& trajectory_now, int start_index){
    start_index = start_sl.start_pos;
    int len = planning_t/conf.step_t+1;
    if(len<5)
        cout << "error: Planner::path_planning: sample error!"<<endl;
    //速度规划
    QP4 = Fitting::quartic4_polynomial(start_sl.s, start_sl.sv, start_sl.sa, end_sl.sv, end_sl.sa , planning_t);
	VectorXf T = VectorXf::LinSpaced(len, 0, planning_t);
    MatrixXf S_out;
    Fitting::cal_point_quartic4(QP4,T,S_out);
    //横向位置规划
    QP5 = Fitting::quintic5_polynomial(start_sl.l,start_sl.dl,start_sl.ddl,end_sl.l,end_sl.dl,end_sl.ddl,
                                        S_out(len-1,0)-start_sl.s);
    VectorXf S;
    S.resizeLike(S_out.col(0));
    for(int i=0;i<S.rows();i++){
        S(i) = S_out(i,0) - start_sl.s;
    }
    MatrixXf L_out;
    Fitting::cal_point_quintic5(QP5 ,S,L_out);
    //生成轨迹
    TrajectoryGeneration::getTrajectory_from_SLT(S_out,L_out,T,refrenceline_Sp, trajectory_now,start_index);
 }