#include "planning/trajectory_stitcher.h"


 bool TrajectoryStitcher::replanningTrajectory(const car_msgs::trajectory_point& car_status,
                            const car_msgs::trajectory& trajectory_now,
                            const double available_l){
    int index=0;
    while(index<trajectory_now.total_path_length-1&&car_status.s-trajectory_now.trajectory_path[index].s>0) index++;
    double distance = (car_status.x - trajectory_now.trajectory_path[index].x)* (car_status.x - trajectory_now.trajectory_path[index].x)+
                        (car_status.y - trajectory_now.trajectory_path[index].y)* (car_status.y - trajectory_now.trajectory_path[index].y);
    if(distance>available_l*available_l)
        return 1;
    else
        return 0;
    }





// int TrajectoryStitcher::ComputeStitchingTrajectory(const Car_Planning_Conf& conf,
//                                                 const Car_State_SL& status_sl,
//                                                 const car_msgs::trajectory& trajectory_now,
//                                                 Car_State_SL& car_start_sl ){
//     //1.将车的当前位置映射到历史轨迹上
//     int start_index=0;
//     while(start_index<trajectory_now.total_path_length-1&&status_sl.s-trajectory_now.trajectory_path[start_index].s>0) start_index++;
    
//     //第一次运行时间是没有偏差的
//     if(first_run_flag){
//         T<<(T0 + conf.keep_t);
//         first_run_flag = 0;
//     }else
//         //预测一秒后的，本来这里要加上1，但由于后面相对时间是从0开始算的，已经加了1，
//         T<<T0;
//     MatrixXf S_out;
//     Fitting::cal_point_quartic4(QP4,T,S_out);
//     VectorXf S(1);
//     S(0) = S_out(0,0) - car_last_sl.s;
//     MatrixXf L_out;
//     Fitting::cal_point_quintic5(QP5 ,S,L_out);
//     int end_index = start_index;
//     while(end_index<trajectory_now.total_path_length-1&&S_out(0,0)-trajectory_now.trajectory_path[end_index].s>0) end_index++;
//     int len1 = end_index - start_index;
//     for(int i=0;i<len1;i++){
//         trajectory_now.trajectory_path[i] = trajectory_now.trajectory_path[i+start_index];
//         trajectory_now.trajectory_path[i].relative_time -=T0;
//         trajectory_now.trajectory_path[i].header.seq = i+1;
//     }
//     //设置起点为end_index当前坐标
//     Car_State_SL start_sl;
//     start_sl.s = S_out(0,0);
//     start_sl.sv = S_out(0,1);
//     start_sl.sa = S_out(0,2);
//     start_sl.h = L_out(0,0);
//     start_sl.dh = L_out(0,1);
//     start_sl.ddh = L_out(0,2);


//     //2.映射点往后一段距离
//     start_index += conf.keep_t/conf.step_t;
//     start_index = min(start_index, trajectory_now.total_path_length);

//     //3.

// }