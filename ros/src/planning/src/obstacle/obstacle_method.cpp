#include "planning/obstacle/obstacle_method.h"
#define MAX_DISTANT 9999.9
// -需要关注的障碍物满足下列条件：
// *与车体的XY坐标系下的距离小于一定值
// *与车体前进方向的夹角小于一定值
bool ObstacleMethod::isconcern(const car_msgs::base_obstacle& b_obst,
                                const car_msgs::trajectory_point& car_status,
                                const ObstacleList_conf& conf){
    double dx = b_obst.xa[0] - car_status.x;
    double dy = b_obst.ya[0] - car_status.y;
    double theta = Interpolating::yaw(dx, dy);
    double distance_xy = sqrt(dx*dx+dy*dy);
    double dtheta = theta - car_status.theta;
    // cout<< "obstacle "<<b_obst.header.seq<<":"<<endl;
    // cout<<"distance_xy:" <<distance_xy<<endl;
    // cout<<"obstacle.theta:" <<theta<<endl;
    // cout<<"car_status.theta:" <<car_status.theta<<endl;
    if(abs(dtheta)<PI/2.0&&distance_xy<40)
        return 1;
    else
        return 0;
};


#define D_STEP 0.5
double ObstacleMethod::distance_Ob_QP(const Obstacle& obs, const VectorXf& QP,
                                        double start_s, double end_s, double t){
    double ds,dl;
    if(obs.sa[0]>end_s){//如果
        dl = obs.la[0] - Fitting::cal_point_quintic5(QP, end_s - start_s);
        ds = obs.sa[0] - end_s;
        return sqrt(dl*dl+ds*ds);
    }
    if(obs.sa[0]<start_s){
        dl = obs.la[0] - Fitting::cal_point_quintic5(QP, 0);
        ds = start_s - obs.sa[0];
        return sqrt(dl*dl+ds*ds);
    }
    //
    // double min_distant2 = MAX_DISTANT;
    // for(double s = 0; s<end_s - start_s; s+=D_STEP){
    //     dl = Fitting::cal_point_quintic5(QP, s);
    //     ds = obs.sa[0] - start_s - s;
    //     min_distant2 = min(min_distant2, dl*dl+ds*ds);
        dl = obs.la[0] - Fitting::cal_point_quintic5(QP, obs.sa[0]-start_s);
        return abs(dl);
}

double ObstacleMethod::distance_Ob_QP(const Obstacle& obs, const MatrixXf& QP,
                                        const vector<double>& s_list, double t){
    int len = QP.rows();
    double min_distant = MAX_DISTANT;
    for(int i= 0;i<s_list.size()-1;i++){
        min_distant = min(min_distant,distance_Ob_QP(obs,QP.row(i),s_list[i],s_list[i+1],t));
    }
    return min_distant;
}
void  ObstacleMethod::XTtoSL(const car_msgs::trajectory& reference_line,
            const Car_State_SL& status_sl,
            Obstacle& obs){
    pair<double, double> sl = Coordinate_converter::POS_to_SL(reference_line,obs.xa[0],obs.ya[0],status_sl.index, status_sl.index+300);
    obs.sa[0] = sl.first;
    obs.la[0] = sl.second;

}