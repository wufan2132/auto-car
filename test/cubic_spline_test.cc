#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

class cubic_spline{
    public:
        int spline(double *in_x,double *in_y,int in_xy_length,double in_spline_step, double *const out_spline_x, double *const out_spline_y);
    private:
//采样点变量
        double origin_xy_length;
        vector<double> origin_Hx;
        vector<double> origin_Hy;
        vector<double> origin_x;
        vector<double> origin_y;
//样条变量
        double spline_xy_length;
        double spline_step;
        vector<double> spline_a;
        vector<double> spline_b;
        vector<double> spline_c;
        vector<double> spline_d;

//矩阵变量
        vector<double> a;
        vector<double> b;
        vector<double> c;
        vector<double> d;
        vector<double> m;
//追赶法中间变量
        vector<double> p;
        vector<double> q;
        vector<double> y;

        void compute_x(double *in_x,double *in_y, double *const out_spline_x, double *const out_spline_y);
        void compute_y(double *in_x,double *in_y, double *const out_spline_x, double *const out_spline_y);
        void set_state(void);
        void compute_m(void);
        void compute_spline( double *const out_spline_x, double *const out_spline_y);
        void clear_variable(void);
};

int cubic_spline::spline(double *in_x,double *in_y,int in_xy_length,double in_spline_step, double *const out_spline_x, double *const out_spline_y){
    origin_xy_length = in_xy_length;
    spline_step = in_spline_step;
    clear_variable();
    compute_x(in_x,in_y,out_spline_x,out_spline_y);
    clear_variable();
    compute_y(in_x,in_y,out_spline_x,out_spline_y);
    return spline_xy_length;
}

void cubic_spline::clear_variable(void){
    origin_Hx.clear();
    origin_Hy.clear();
    origin_x.clear();
    origin_y.clear();
    //样条变量
    spline_a.clear();
    spline_b.clear();
    spline_c.clear();
    spline_d.clear();
    //矩阵变量
    a.clear();
    b.clear();
    c.clear();
    d.clear();
    m.clear();
    //追赶法中间变量
    p.clear();
    q.clear();
    y.clear();
}
void cubic_spline::compute_x(double *in_x,double *in_y, double *const out_spline_x, double *const out_spline_y){
    //求s ->x
    origin_x.push_back(0);
    origin_y.push_back(in_x[0]);
    for(int index = 1;index < origin_xy_length;index++){
        double dx = in_x[index] - in_x[index-1];
        double dy = in_y[index] - in_y[index-1];
        double ds = sqrt(dx*dx + dy*dy);
//求x 和x差
        origin_Hx.push_back(ds);
        origin_x.push_back(origin_x[index-1] + ds);
//求y 和y差
        origin_y.push_back(in_x[index]);
        origin_Hy.push_back(dx);

    }

    set_state();
    compute_m();
    compute_spline(out_spline_x,out_spline_x);
}
void cubic_spline::compute_y(double *in_x,double *in_y, double *const out_spline_x, double *const out_spline_y){
    //求s ->x
    origin_x.push_back(0);
    origin_y.push_back(in_y[0]);
    for(int index = 1;index < origin_xy_length;index++){  
        double dx = in_x[index] - in_x[index-1];
        double dy = in_y[index] - in_y[index-1];
        double ds = sqrt(dx*dx + dy*dy);
//求x 和x差
        origin_Hx.push_back(ds);
        origin_x.push_back(origin_x[index-1] + ds);
//求y 和y差
        origin_y.push_back(in_y[index]);
        origin_Hy.push_back(dy);


    }

    set_state();
    compute_m();
    compute_spline(out_spline_x,out_spline_y);
}

void cubic_spline::set_state(void){
//求A矩阵
    b.push_back(1);
    c.push_back(0);
    for(vector<double>::iterator it = (origin_Hx.begin()+1);it < origin_Hx.end();it++){  
        a.push_back(*(it-1));
        b.push_back(2*(*it + *(it-1)));
        c.push_back(*it);
    }
    a.push_back(0);
    b.push_back(1);
//求B矩阵
    d.push_back(0);
    for(int index = 1;index < origin_xy_length-1;index++){ 
        double d_temp = origin_Hy[index]/origin_Hx[index] - origin_Hy[index-1]/origin_Hx[index-1];
        d_temp = d_temp*6;
        d.push_back(d_temp);
    }
    d.push_back(0);
}

void cubic_spline::compute_m(void){
//追赶法求m
    q.push_back(b.front());
    y.push_back(d.front());
    for(int index = 1;index < origin_xy_length;index++){ 
        p.push_back(a[index-1]/q[index-1]);
        q.push_back(b[index] - p[index-1]*c[index-1]);
        y.push_back(d[index]-p[index-1]*y[index-1]);
    }
    m.push_back(y.back()/q.back());
    for(int index = origin_xy_length -2;index >= 0;index--){ 
        double m_temp = m.front();
        m.insert(m.begin(),(y[index]-c[index]*m_temp)/q[index]);
    }
}

void cubic_spline::compute_spline( double *const out_spline_x, double *const out_spline_y){
//求样条参数a b c d 
    for(int index = 0;index < origin_xy_length-1;index++){ 
        spline_a.push_back(origin_y[index]);
        spline_b.push_back(origin_Hy[index]/origin_Hx[index] - (origin_Hx[index]*m[index+1]+2*origin_Hx[index]*m[index])/6);
        spline_c.push_back(m[index]/2);
        spline_d.push_back((m[index+1]-m[index])/(6*origin_Hx[index]));
    }
//根据步进算样条曲线
    double x_add = origin_x[0];
    int i = 0;
    for(int index = 0;index < origin_xy_length;index++){
        for(;x_add < origin_x[index+1];x_add += spline_step){
            //out_spline_x[i] = x_add;
            double x_offect = x_add - origin_x[index];
            double spline_y_temp = spline_a[index] + spline_b[index]*x_offect + spline_c[index]*x_offect*x_offect + spline_d[index]*x_offect*x_offect*x_offect;
            out_spline_y[i] = spline_y_temp;
            i++;
        }
    }
    spline_xy_length = i;
}

int main()
{
    cubic_spline cubic_spline_test;


    double spline_step = 0.1;
    double origin_xy_length = 4;
    double pose_x[13]={-3,-2,1,3};
    double pose_y[13]={2,0,3,1};

    double *const out_spline_x=(double*)malloc(sizeof(double)*1000);
    double *const out_spline_y=(double*)malloc(sizeof(double)*1000);

    int path_length = cubic_spline_test.spline(pose_x,pose_y,origin_xy_length,spline_step,out_spline_x,out_spline_y);

    cout<< "------------------x" << endl;
    for(int i = 0;i<path_length;i++){
        cout<< out_spline_x[i] << endl;
    }
    cout<< "------------------y" << endl;
    for(int i = 0;i<path_length;i++){
        cout<< out_spline_y[i] << endl;
    }
    free(out_spline_x);
    free(out_spline_y);
    return 0;
}