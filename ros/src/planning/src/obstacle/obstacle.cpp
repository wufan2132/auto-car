#include "planning/obstacle/obstacle.h"


Obstacle::Obstacle(){
    sa.resize(4);
    la.resize(4);
};

Obstacle::Obstacle(const car_msgs::base_obstacle& object)
:car_msgs::base_obstacle(object){
    sa.resize(4);
    la.resize(4);
};