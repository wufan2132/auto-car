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

    chassisCommand_publisher = controller_NodeHandle.advertise<car_msgs::control>("prius", 1); 
}

void Controller::ProduceControlCommand(car_msgs::control *cmd){

    lon_controller_.ComputeControlCommand(&localization_,&chassis_,&trajectory_,cmd);
}

void Controller::CheckInput(void){

}

void Controller::SendCmd(car_msgs::control *control_cmd){
    chassisCommand_publisher.publish(*control_cmd);
}

void Controller::OnTimer(const ros::TimerEvent&){
    car_msgs::control control_cmd;

    CheckInput();
    ProduceControlCommand(&control_cmd);
    SendCmd(&control_cmd);
}

void Controller::localization_topic_callback(const car_msgs::localization &localization){
    localization_.x = localization.x;
    localization_.y = localization.y;
    localization_.z = localization.z;
    localization_.speed = localization.speed;
    localization_.accel = localization.accel;
    localization_.yaw = localization.yaw;
}
void Controller::chassis_topic_callback(const car_msgs::chassis &chassis){
    chassis_.speed = chassis.speed;
    chassis_.acc = chassis.acc;
}

void Controller::trajectory_topic_callback(const car_msgs::trajectory &trajectory){

}