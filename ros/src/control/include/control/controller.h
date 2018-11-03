#include "control/lon_controller.h"
#include "ros/ros.h"

class Controller{
public:
    void Init(void);
    void ProduceControlCommand(car_msgs::control_cmd *control_cmd);
    void CheckInput(void);
    void SendCmd(car_msgs::control_cmd *control_cmd);

    void OnTimer(const ros::TimerEvent&);
    void chassis_topic_callback(const car_msgs::chassis &chassis);
    void localization_topic_callback(const car_msgs::localization &localization);
    void path_topic_callback(const car_msgs::path_point &path_point);

    ros::NodeHandle controller_NodeHandle;
    ros::Publisher chassisCommand_publisher;

private:

    car_msgs::localization localization_;
    car_msgs::chassis chassis_;
    car_msgs::path_point path_point_;

    LonController lon_controller_;
};