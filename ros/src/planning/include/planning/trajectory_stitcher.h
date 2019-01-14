#pragma once
#include "planning/common.h"


class TrajectoryStitcher {
 public:
//  int ComputeStitchingTrajectory(const Car_Planning_Conf& conf,
//                                 const Car_State_SL& status_sl,
//                                 const car_msgs::trajectory& trajectory_now,
//                                 Car_State_SL& car_start_sl );

 static bool replanningTrajectory(const car_msgs::trajectory_point& car_status,
                            const car_msgs::trajectory& trajectory_now,
                            const double available_l);

};


