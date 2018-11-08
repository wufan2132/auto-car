#ifndef _CONTROL_H_
#define _CONTROL_H_ 

#include "ros/ros.h"
#include "control/controller.h"
#include "control/lon_controller.h"
#include "control/lat_controller.h"

namespace control {

class Control{
public:
    void Init(void);
    void ProduceControlCommand(car_msgs::control_cmd *control_cmd);
    void CheckInput(void);
    void SendCmd(car_msgs::control_cmd *control_cmd);

    void OnTimer(const ros::TimerEvent&);
    void chassis_topic_callback(const car_msgs::chassis &chassis);
    void localization_topic_callback(const car_msgs::localization &localization);
    void path_topic_callback(const car_msgs::trajectory &trajectory_path);

    ros::NodeHandle control_NodeHandle;
    ros::Publisher chassisCommand_publisher;

    
private:

    VehicleState vehicle_state_;
    SimpleLateralDebug debug_;
     
    car_msgs::localization localization_;
    car_msgs::chassis chassis_;
    car_msgs::trajectory trajectory_path_;

    LonController lon_controller_;
    LatController lat_controller_;
};
}
#endif  //_CONTROLLER_H_