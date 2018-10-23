#include "control/lon_controller.h"
#include "ros/ros.h"

class Controller{
public:
    void Init(void);
    void ProduceControlCommand(msgs::chassisCommand *cmd);
    void CheckInput(void);
    void SendCmd(msgs::chassisCommand *cmd);

    void OnTimer(const ros::TimerEvent&);
    void chassis_topic_callback(const msgs::chassis &chassis);
    void localization_topic_callback(const msgs::localization &localization);
    void trajectory_topic_callback(const msgs::trajectory &trajectory);

    ros::NodeHandle controller_NodeHandle;
    ros::Publisher chassisCommand_publisher;

private:

    msgs::localization localization_;
    msgs::chassis chassis_;
    msgs::trajectory trajectory_;

    LonController lon_controller_;
};