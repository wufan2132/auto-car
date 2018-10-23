#include "control/controller.h"
#include "yaml-cpp/yaml.h"
#define LON_CONTROLLER_CONF_DIR "/home/gyl/my-code/auto-car/ros/src/control/src/conf/control.yaml"
using namespace std;

void Controller::Init(void){
    YAML::Node controller_conf = YAML::LoadFile(LON_CONTROLLER_CONF_DIR);
    LonControllerConf lon_controller_conf;

    lon_controller_conf.ts = controller_conf["lon_controller_conf"]["ts"].as<double>();
    lon_controller_conf.station_pid_conf.integrator_enable = controller_conf["lon_controller_conf"]["station_pid_conf"]["integrator_enable"].as<bool>();
    lon_controller_conf.station_pid_conf.integrator_saturation_level = controller_conf["lon_controller_conf"]["station_pid_conf"]["integrator_saturation_level"].as<double>();
    lon_controller_conf.station_pid_conf.kp = controller_conf["lon_controller_conf"]["station_pid_conf"]["kp"].as<double>();
    lon_controller_conf.station_pid_conf.ki = controller_conf["lon_controller_conf"]["station_pid_conf"]["ki"].as<double>();
    lon_controller_conf.station_pid_conf.kd = controller_conf["lon_controller_conf"]["station_pid_conf"]["kd"].as<double>();
    lon_controller_conf.station_pid_conf.kaw = controller_conf["lon_controller_conf"]["station_pid_conf"]["kaw"].as<double>();
    lon_controller_conf.station_pid_conf.output_saturation_level = controller_conf["lon_controller_conf"]["station_pid_conf"]["output_saturation_level"].as<double>();

    lon_controller_conf.speed_pid_conf.integrator_enable = controller_conf["lon_controller_conf"]["speed_pid_conf"]["integrator_enable"].as<bool>();
    lon_controller_conf.speed_pid_conf.integrator_saturation_level = controller_conf["lon_controller_conf"]["speed_pid_conf"]["integrator_saturation_level"].as<double>();
    lon_controller_conf.speed_pid_conf.kp = controller_conf["lon_controller_conf"]["speed_pid_conf"]["kp"].as<double>();
    lon_controller_conf.speed_pid_conf.ki = controller_conf["lon_controller_conf"]["speed_pid_conf"]["ki"].as<double>();
    lon_controller_conf.speed_pid_conf.kd = controller_conf["lon_controller_conf"]["speed_pid_conf"]["kd"].as<double>();
    lon_controller_conf.speed_pid_conf.kaw = controller_conf["lon_controller_conf"]["speed_pid_conf"]["kaw"].as<double>();
    lon_controller_conf.speed_pid_conf.output_saturation_level = controller_conf["lon_controller_conf"]["speed_pid_conf"]["output_saturation_level"].as<double>();
    
    lon_controller_.Init(&lon_controller_conf);

    chassisCommand_publisher = controller_NodeHandle.advertise<msgs::chassisCommand>("chassisCommand_topic", 1); 
}

void Controller::ProduceControlCommand(msgs::chassisCommand *cmd){

    lon_controller_.ComputeControlCommand(&localization_,&chassis_,&trajectory_,cmd);
}

void Controller::CheckInput(void){

}

void Controller::SendCmd(msgs::chassisCommand *cmd){
    // chassisCommand_publisher.publish(*cmd);
}

void Controller::OnTimer(const ros::TimerEvent&){
    msgs::chassisCommand chassisCommand;

    CheckInput();
    ProduceControlCommand(&chassisCommand);
    SendCmd(&chassisCommand);
}

void Controller::localization_topic_callback(const msgs::localization &localization){
    localization_.x = localization.x;
    localization_.y = localization.y;
    localization_.z = localization.z;
    localization_.speed = localization.speed;
    localization_.accel = localization.accel;
    localization_.yaw = localization.yaw;
}
void Controller::chassis_topic_callback(const msgs::chassis &chassis){
    chassis_.speed = chassis.speed;
    chassis_.acc = chassis.acc;
}

void Controller::trajectory_topic_callback(const msgs::trajectory &trajectory){

}