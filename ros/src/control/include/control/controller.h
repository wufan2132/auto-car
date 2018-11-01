#include "control/lon_controller.h"
#include "ros/ros.h"

class Controller{
public:
    void Init(void);
    void ProduceControlCommand(car_msgs::control *cmd);
    void CheckInput(void);
    void SendCmd(car_msgs::control *cmd);

    void OnTimer(const ros::TimerEvent&);
    void chassis_topic_callback(const car_msgs::chassis &chassis);
    void localization_topic_callback(const car_msgs::localization &localization);
    void trajectory_topic_callback(const car_msgs::trajectory &trajectory);

    ros::NodeHandle controller_NodeHandle;
    ros::Publisher chassisCommand_publisher;

private:

    car_msgs::localization localization_;
    car_msgs::chassis chassis_;
    car_msgs::trajectory trajectory_;

    LonController lon_controller_;
};