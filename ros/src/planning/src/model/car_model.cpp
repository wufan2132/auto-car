#include "planning/car_model.h"

#define FINDNUMS 270 //每次向后查找多少个点 假设采样间隔splice = 0.1m,车速100km/h (27m/s),1s 会经过270个点

bool Coordinate_converter::POS_to_SL(const car_msgs::trajectory& reference_line,car_msgs::trajectory_point& point,Car_State_SL& status_sl){
    if(!point.header.seq>0){
        //debug
        ROS_WARN("Coordinate_converter::POS_to_SL: trajectory_point is not received!");
        return 0;
    }
    //cout<<"status_sl.index:"<<status_sl.index<<endl;
    int end_index = min(status_sl.index+FINDNUMS,int(reference_line.total_path_length)-2);
    //cout<<"end_index:"<<end_index<<endl;
    for(int i=status_sl.index;i<end_index;i++){
        float distance0 = (point.x - reference_line.trajectory_path[i].x)*(point.x - reference_line.trajectory_path[i].x) +
        (point.y - reference_line.trajectory_path[i].y)* (point.y - reference_line.trajectory_path[i].y);
        float distance1 = (point.x - reference_line.trajectory_path[i+1].x)*(point.x - reference_line.trajectory_path[i+1].x) +   
        (point.y - reference_line.trajectory_path[i+1].y)* (point.y - reference_line.trajectory_path[i+1].y);  
        if(distance0>distance1)
            continue;
        else{
            status_sl.index = i;
            break;
        }          
    }
    //求点到直线的距离
    float A = reference_line.trajectory_path[status_sl.index].y - reference_line.trajectory_path[status_sl.index+1].y;
    float B = reference_line.trajectory_path[status_sl.index+1].x - reference_line.trajectory_path[status_sl.index].x;
    float C = reference_line.trajectory_path[status_sl.index+1].y*(reference_line.trajectory_path[status_sl.index].x - reference_line.trajectory_path[status_sl.index+1].x) -
            reference_line.trajectory_path[status_sl.index+1].x*(reference_line.trajectory_path[status_sl.index].y - reference_line.trajectory_path[status_sl.index+1].y);
    status_sl.l = (A*point.x+B*point.y+C)/sqrt(A*A+B*B);
    //cout<<"h:"<<status_sl.l<<endl;
    //求垂足
    float x_ = (B*B*point.x-A*B*point.y-A*C)/(A*A+B*B);
    float y_ = (-A*B*point.x+A*A*point.y-B*C)/(A*A+B*B);
    //根据垂足求s
    status_sl.s = reference_line.trajectory_path[status_sl.index].s + 
    (reference_line.trajectory_path[status_sl.index+1].s - reference_line.trajectory_path[status_sl.index].s)*
    (x_ - reference_line.trajectory_path[status_sl.index].x)/
    (reference_line.trajectory_path[status_sl.index+1].x - reference_line.trajectory_path[status_sl.index].x);
    point.s = status_sl.s;
    //cout<<"s:"<<status_sl.s<<endl;
    //求夹角
    //cout<<"cal_theta"<<endl;
    status_sl.theta = reference_line.trajectory_path[status_sl.index].theta;
    float theta = point.theta - reference_line.trajectory_path[status_sl.index].theta;
    float tan_theta = tan(theta);
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    float one_minus_kappa_r_d = 1 - reference_line.trajectory_path[status_sl.index].kappa * status_sl.l;
    //求sv
    status_sl.sv = point.speed*cos_theta/one_minus_kappa_r_d;
    //求sa
    status_sl.sa = point.accel * cos_theta / one_minus_kappa_r_d;
    //求dh/ds 
    status_sl.dl = one_minus_kappa_r_d*tan_theta;
    //求dh/d2s
    status_sl.ddl = -reference_line.trajectory_path[status_sl.index].kappa * status_sl.dl* tan_theta;
    //debug
    //ROS_INFO("index:%d theta:%0.2f s:%.2f sv:%.2f sa:%.6f h:%.2f dh:%.2f ddh:%.6f",
    //status_sl.index,theta,status_sl.s,status_sl.sv,status_sl.sa,status_sl.l,status_sl.dl,status_sl.ddl);
    return 0;
}

//
pair<double, double> Coordinate_converter::POS_to_SL(const car_msgs::trajectory& reference_line, double x, double y, int start, int end){
    pair<double, double> sl;
    //int end = start + FINDNUMS;
    int pos = 0;
    while(end - start > 1){
        pos = (start + end)/2;
        float distance0 = (x - reference_line.trajectory_path[pos].x)*(x - reference_line.trajectory_path[pos].x) +
            (y - reference_line.trajectory_path[pos].y)* (y - reference_line.trajectory_path[pos].y);
        float distance1 = (x - reference_line.trajectory_path[pos+1].x)*(x - reference_line.trajectory_path[pos+1].x) +   
            (y - reference_line.trajectory_path[pos+1].y)* (y - reference_line.trajectory_path[pos+1].y);  
        if(distance0>distance1){
            start = pos;
        }else {
            end = pos;
        }
    }
    //pos = start+1;
    //求点到直线的距离
    float A = reference_line.trajectory_path[pos].y - reference_line.trajectory_path[pos+1].y;
    float B = reference_line.trajectory_path[pos+1].x - reference_line.trajectory_path[pos].x;
    float C = reference_line.trajectory_path[pos+1].y*(reference_line.trajectory_path[pos].x - reference_line.trajectory_path[pos+1].x) -
            reference_line.trajectory_path[pos+1].x*(reference_line.trajectory_path[pos].y - reference_line.trajectory_path[pos+1].y);
    sl.second = (A*x+B*y+C)/sqrt(A*A+B*B);
    //cout<<"h:"<<status_sl.l<<endl;
    //求垂足
    float x_ = (B*B*x-A*B*y-A*C)/(A*A+B*B);
    float y_ = (-A*B*x+A*A*y-B*C)/(A*A+B*B);
    //根据垂足求s
    sl.first = reference_line.trajectory_path[pos].s + 
    (reference_line.trajectory_path[pos+1].s - reference_line.trajectory_path[pos].s)*
    (x_ - reference_line.trajectory_path[pos].x)/
    (reference_line.trajectory_path[pos+1].x - reference_line.trajectory_path[pos].x);
    return sl;
}


void Coordinate_converter::SL_to_POS(const double s, const double l,
     const MatrixXf& sx, const MatrixXf& sy, car_msgs::trajectory_point& point, const int start_index){
	int idx;
	double dx, dy;
	VectorXf sx_X = sx.row(0);
    //计算 rx,ry,rdx,rdy
    double rx,ry,rdx,rdy;

    idx = search_index(s, sx_X);
    // cout<<"idx"<<idx<<endl;

    //rx
    dx = s - sx(0, idx);
    rx = sx(2, idx) + sx(3, idx) * dx + sx(4, idx) * dx * dx + sx(5, idx) * dx * dx * dx;
    rdx = sx(3, idx) + 2 * sx(4, idx) * dx + 3 * sx(5, idx)*dx*dx;
    //ry
    dy = s - sy(0, idx);
    ry = sy(2, idx) + sy(3, idx) * dy + sy(4, idx) * dy * dy + sy(5, idx) * dy * dy * dy;
    rdy = sy(3, idx) + 2 * sy(4, idx) * dy + 3 * sy(5, idx)*dy*dy;
    //计算rtheta
    double rtheta = Interpolating::yaw(rdx,rdy);
    //计算x y
    point.x = rx - l*sin(rtheta);
    point.y = ry + l*cos(rtheta);
    point.z = 0;

    //cout<<"index:"<<start_index<<"  rx:"<<rx<<"  ry:"<<ry<<"  dx:"<<dx<<" dy:"<<dy<<" s:"<<s  <<endl;
}

//思路：二分查找与顺序查找并行
int Coordinate_converter::search_index(double st, VectorXf& s){
    //远离参数
    static const int S_LIMIT = 30;
    //
    static int pos = 0;
    int len = s.rows();
    // cout<<"st:"<<st<<endl;
    // cout<<"s:"<<endl;
    // cout<<s<<endl;
    //输入判断
    if (st <=s(0)) pos = 0;
	else if (st >= s(len - 1)){
        pos = len - 1;
    }
    else if(st >= s(pos) && st - s(pos) < S_LIMIT){//如果与目标位置间距较小
        while (st >= s(pos+1)) pos++;
        //cout<<"Coordinate_converter::search_index: 顺序查找: "<<pos<<endl;
    }
    else {//二分查找
        int start = 0;
        int end = len;
        while(end - start > 1){
            pos = (start + end)/2;
            if(st >= s(pos)){
                start = pos;
            }else{
                end = pos;
            }
        }
        pos = start;
        //cout<<"Coordinate_converter::search_index: 二分查找: "<<pos<<endl;
    }
    return pos;



    // static int start_pos=0;
   	// static int pos = start_pos;
    // int len = s.rows();
    // if (index==0)
	// 	pos = start_pos;

    // if (st <=0) pos = 0;
	// else if (st >= s[len - 1]){
    //     pos = len - 1;
    // }
    // else if(st < s(pos)){
    //     while(st > s(pos)) pos--;
    // }
    // else{
    //     while (st >= s[pos+1]) pos++;
    // }

    // if(index==0) 
    //     start_pos = pos;
    // return pos;
}