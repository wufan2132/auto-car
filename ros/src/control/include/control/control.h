#ifndef _CONTROL_H_
#define _CONTROL_H_ 

#include "ros/ros.h"
#if MPC_OR_LQR
    #include "control/lon_controller.h"
    #include "control/lat_controller.h"
#else
    #include "control/mpc_controller.h"
#endif

#include "car_msgs/debug.h"

namespace control {

class Control{
public:
    void Init(void);
    void ProduceControlCommand(car_msgs::control_cmd &control_cmd);
    bool CheckInput(void);
    void SendCmd(car_msgs::control_cmd &control_cmd);
    void Debug(void);

    void OnTimer(const ros::TimerEvent&);
    void chassis_topic_callback(const car_msgs::chassis &chassis);
    void localization_topic_callback(const car_msgs::localization &localization);
    void path_topic_callback(const car_msgs::trajectory &trajectory_path);

    ros::NodeHandle control_NodeHandle;
    ros::Publisher chassisCommand_publisher;
    ros::Publisher debug_publisher;

    
private:
    int control_mode_;
    int debug_mode_;

    car_msgs::vehicle_state vehicle_state_;
    car_msgs::debug debug_;

    car_msgs::localization localization_;
    car_msgs::chassis chassis_;
    car_msgs::trajectory trajectory_path_;

#if MPC_OR_LQR
    LonController lon_controller_;
    LatController lat_controller_;
#else
    MPCController mpc_controller_;
#endif
};
}
#endif  //_CONTROLLER_H_