#pragma once
#include "planning/common.h"
#include "planning/car_model.h"

using namespace Eigen;
using namespace std;

class TrajectoryGeneration{
public:
    static bool getTrajectory_from_SLT(const MatrixXf& S,const MatrixXf& L,const VectorXf& T,
                           const Spline_Out* refrenceline_Sp, car_msgs::trajectory& trajectory,int start_index);
};