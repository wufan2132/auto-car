#include "planning/planning.h"


void Car_Planning::Init(void){
}

void Car_Planning::RunOnce(void){
    //origin_path to this_path
}

void Car_Planning::Get_path(const car_msgs::path& path){
    origin_path = path;
}