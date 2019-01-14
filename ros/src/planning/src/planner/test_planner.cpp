#include "planning/planner/test_planner.h"

TestPlanner::TestPlanner(YAML::Node yaml_conf)
:Planner(yaml_conf){
    conf.available_l= yaml_conf["available_l"].as<double>();
    conf.aim_speed= yaml_conf["aim_speed"].as<double>();
    conf.step_t = yaml_conf["step_t"].as<double>();
    conf.planning_t= yaml_conf["planning_t"].as<double>();
    conf.planning_s= yaml_conf["planning_s"].as<double>();
    conf.keep_t = yaml_conf["keep_t"].as<double>();
    conf.speed_correction = yaml_conf["speed_correction"].as<double>();
    conf.speed_min_limit = yaml_conf["speed_min_limit"].as<double>();

    sampler = new SamplerPoint(yaml_conf["SamplerPoint_conf"]); 
    dpgraph = new DpRoadGraph(yaml_conf);  
    stgraph = new DpStGraph(yaml_conf);
}


Car_State_SL TestPlanner::get_start_point(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl
                                        ,const car_msgs::trajectory& reference_line,car_msgs::trajectory& trajectory_now){
     static bool replanning_flag = 0;
     static double last_initsl_S = 0;
     static int last_start_index = 0;
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
        start_sl.t = 0;
        last_initsl_S = start_sl.s;
        last_start_index = 0;
        ROS_INFO("TestPlanner::get_start_point: replanning!");
        return start_sl;
     }
     else{
        int start_index=0;
        while(start_index<trajectory_now.total_path_length-1&&status_sl.s-trajectory_now.trajectory_path[start_index].s>0) start_index++;
        float T0 = trajectory_now.trajectory_path[start_index].relative_time;
        VectorXf T(1);
        int end_index2 = 0;
        //第一次运行时间是没有偏差的
        if(replanning_flag){
            T<<(T0 + conf.keep_t);
            replanning_flag = 0;

            while(T(0)<trajectory_sl[end_index2].t) end_index2++;
        }else{
            //预测一秒后的，本来这里要加上1，但由于后面相对时间是从0开始算的，已经加了1，
            T<<T0;
            while(T(0)<trajectory_sl[end_index2].t) end_index2++;
            end_index2 += last_start_index;
        }
        last_start_index = start_index;
        // MatrixXf S_out;
        // Fitting::cal_point_quartic4(QPts,T,S_out);
        // VectorXf S(1);
        // S(0) = S_out(0,0);
        // MatrixXf L_out;
        // Fitting::cal_point_quintic5(QPsl ,S,L_out);
        // int end_index = start_index+ (conf.keep_t/conf.step_t);
        // while(end_index<trajectory_now.total_path_length-1 && S_out(0,0)-trajectory_now.trajectory_path[end_index].s>0) end_index++;
        // int len1 = end_index - start_index;

        // for(int i=0;i<len1;i++){
        //     trajectory_now.trajectory_path[i] = trajectory_now.trajectory_path[i+start_index];
        //     trajectory_now.trajectory_path[i].relative_time -=T0;
        //     trajectory_now.trajectory_path[i].header.seq = i+1;
        // }
        // //设置起点为end_index当前坐标
        // Car_State_SL start_sl;
        // // start_sl.start_pos = status_sl.index;
        // // Coordinate_converter::POS_to_SL(reference_line,trajectory_now.trajectory_path[end_index],start_sl);
        // start_sl.s   = S_out(0,0) + last_initsl_S;
        // start_sl.sv  = S_out(0,1);
        // start_sl.sa  = S_out(0,2);
        // start_sl.l   = L_out(0,0);
        // start_sl.dl  = L_out(0,1);
        // start_sl.ddl = L_out(0,2);
        // start_sl.start_pos = len1;
        // start_sl.t = conf.keep_t;
        // last_initsl_S = start_sl.s;
        ////////////////////////////////////////////////
    
        Car_State_SL start_sl2;
        start_sl2 = trajectory_sl[end_index2];
        start_sl2.start_pos = end_index2 - start_index;
        start_sl2.t = conf.keep_t;
        // start_sl2.dl = L_out(0,1);
        // start_sl2.ddl = L_out(0,2);
        cout << "  s2:"<<start_sl2.s<<endl;
        cout << "  l2:"<<start_sl2.l<<endl;
        cout << "  sv2:"<<start_sl2.sv<<endl;
        cout << "  sa2:"<<start_sl2.sa<<endl;
        cout << "  dl2:"<<start_sl2.dl<<endl;
        cout << "  ddl2:"<<start_sl2.ddl<<endl;
        // cout<<"T"<<endl;
        // cout<<T<<endl;
        // cout<<"S_out"<<endl;
        // cout<<S_out<<endl;
        // cout<<"L_out"<<endl;
        // cout<<L_out<<endl;
        //cout<<"start_pos:"<<start_index<<"  end_pos:"<<end_index<<"  len1:"<< start_sl.start_pos << endl;
        cout<<"start_pos:"<<start_index<<"  end_pos:"<<end_index2<<endl;
        return start_sl2;
     }
}

 void TestPlanner::get_current_line(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl,
                                         const Spline_Out* refrenceline_Sp,const car_msgs::trajectory& reference_line, car_msgs::trajectory& trajectory_now){
    /*****************获得采样的起始点***********************/
    Car_State_SL start_sl = get_start_point(car_status,status_sl,reference_line, trajectory_now);
    // cout<<"status_sl.s: "<<status_sl.s<<endl;
    // cout<<"status_sl.l: "<<status_sl.l<<endl;
    // cout<<"start_sl.s: "<<start_sl.s<<endl;
    // cout<<"start_sl.l: "<<start_sl.l<<endl;
    
    sampler->reset(start_sl);
    /***SL采样***/
    vector<vector<Car_State_SL> > SamplerPointsSL;
    sampler->getpointsSL(conf.planning_t, SamplerPointsSL);
    dpgraph->reset(start_sl,status_sl,sampler->Snum);
    dpgraph->process(SamplerPointsSL, &min_cost_path);
    //获得sl曲线
    QPsl.resize(min_cost_path.size(),6);
    for(int i = 0;i<min_cost_path.size()-1;i++){
        // cout<<"minQP5"<<endl;
        // cout<<min_cost_path[i+1].minQP5<<endl;
        QPsl.row(i) = min_cost_path[i+1].minQP5;
    }
    cout<<"QPsl:"<<endl;
    cout<<QPsl<<endl;

    //QPsl = min_road_Node.minQP5;
    double planning_l = min_cost_path.back().l;
    //cout<<"minscost_L:"<<min_road_Node.minCost<<endl;
    /***ST采样***/
    vector<Car_State_SL> SamplerPointsT;
    sampler->getpointsT(planning_l, conf.planning_s, SamplerPointsT);
    StGraphNode min_st_Node;
    stgraph->reset(start_sl,status_sl,1,conf.aim_speed);
    stgraph->process(SamplerPointsT, &min_st_Node);
    QPts = min_st_Node.minQP4;
    //cout<<"minscost_T:"<<min_st_Node.minCost<<endl;
    //生成路径
    path_generate(QPsl, QPts, refrenceline_Sp, start_sl, trajectory_now);
    for(int i=start_sl.start_pos;i<trajectory_now.total_path_length;i++)
        trajectory_now.trajectory_path[i].relative_time += start_sl.t;
    /************debug 1***********/
    // for(int i=0;i<len;i++)
    // cout<<
    // trajectory_now.trajectory_path[start_index+i].header.seq<<","<<
    // trajectory_now.trajectory_path[start_index+i].x<<","<<
    // trajectory_now.trajectory_path[start_index+i].y<<","<<
    // trajectory_now.trajectory_path[start_index+i].theta<<","<<
    // trajectory_now.trajectory_path[start_index+i].kappa<<endl;
    /************debug 2***********/
    // for(int i=0;i<trajectory_now.total_path_length;i++)
    // cout<<
    // trajectory_now.trajectory_path[i].header.seq<<"."<<
    // " s:"<<trajectory_now.trajectory_path[i].s<<
    // " t:"<<trajectory_now.trajectory_path[i].relative_time<<
    // " x:"<<trajectory_now.trajectory_path[i].x<<
    // " y:"<<trajectory_now.trajectory_path[i].y<<","<<
    // " theta:"<<trajectory_now.trajectory_path[i].theta<<","<<
    // " kappa:"<<trajectory_now.trajectory_path[i].kappa<<endl;
    return;
 }

void TestPlanner::process(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl,
                                 const Spline_Out* refrenceline_Sp, const car_msgs::trajectory& reference_line, car_msgs::trajectory& trajectory_now){
    static int count = 0;
    count++;
    get_current_line(car_status, status_sl, refrenceline_Sp, reference_line,trajectory_now);
    //添加header
    trajectory_now.header.seq = count;
    //保存车体参数
    car_last_sl = status_sl;
}

void TestPlanner::path_generate(const MatrixXf& qpsl,const VectorXf& qpts,
                                const Spline_Out* refrenceline_Sp,
                                const Car_State_SL& start_sl,
                                car_msgs::trajectory& trajectory_now){

    double planning_t = conf.planning_t-start_sl.t; //规划时间
    //cout<<"conf.planning_t:"<<conf.planning_t<<endl;
    int len = (conf.planning_t-start_sl.t)/conf.step_t+1;
    if(len<5)
        ROS_WARN("TestPlanner::path_generate: sample error!");
	VectorXf T = VectorXf::LinSpaced(len, 0, planning_t);

    MatrixXf S_out;
    Fitting::cal_point_quartic4(qpts, T, S_out);
    VectorXf S = S_out.col(0);
    MatrixXf L_out(len, 4);
    int si = 0;
    int index = 1;
    while(si<len){
        if(index >= min_cost_path.size() || S(si)<min_cost_path[index].s){
            VectorXf Ltemp;
            Fitting::cal_point_quintic5(qpsl, S(si), Ltemp);
            L_out.row(si) = Ltemp;
            si++;
        }
        else {
            index ++;
        }
    }
    

    Fitting::cal_point_quintic5(qpsl, S, L_out);
    for(int i=0;i<S.rows();i++){
        S_out(i,0) += start_sl.s;
    }
    //保存
    trajectory_sl.resize(len);
    for(int i=0;i<len;i++){
        trajectory_sl[i].s   = S_out(i,0);
        trajectory_sl[i].sv  = S_out(i,1);
        trajectory_sl[i].sa  = S_out(i,2);
        trajectory_sl[i].l   = L_out(i,0);
        trajectory_sl[i].dl  = L_out(i,1);
        trajectory_sl[i].ddl = L_out(i,2);
        trajectory_sl[i].t = T(i);
    }
    //check
    for(int i=0;i<len-1;i++){
        if(S_out(i+1,0)-S_out(i,0)<0|| //S倒走
             abs(L_out(i+1,0) - L_out(i,0))>2) //横向跳动太大
          ROS_WARN("TestPlanner::path_generate: qp cal error!");   
    }

    // cout<<"qpts"<<endl;
    // cout<<qpts<<endl;
    // cout<<"qpsl"<<endl;
    // cout<<qpsl<<endl;

    // cout<<"Sout:" <<endl;
    // cout<<S_out<<endl;
    // cout<<"Lout:" <<endl;
    // cout<<L_out<<endl;
    //生成轨迹
    TrajectoryGeneration::getTrajectory_from_SLT(S_out,L_out,T,refrenceline_Sp, trajectory_now, start_sl.start_pos);
 }