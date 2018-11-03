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

    chassisCommand_publisher = controller_NodeHandle.advertise<car_msgs::control_cmd>("prius", 1); 
}

void Controller::ProduceControlCommand(car_msgs::control_cmd *control_cmd){
    control_cmd->header = chassis_.header;

    path_point_.position.x = 100;
    path_point_.speed = 0;

    lon_controller_.ComputeControlCommand(&localization_,&chassis_,&path_point_,control_cmd);
}

void Controller::CheckInput(void){

}

void Controller::SendCmd(car_msgs::control_cmd *control_cmd){
    chassisCommand_publisher.publish(*control_cmd);
}

void Controller::OnTimer(const ros::TimerEvent&){
    car_msgs::control_cmd control_cmd;

    CheckInput();
    ProduceControlCommand(&control_cmd);
    SendCmd(&control_cmd);
}

void Controller::localization_topic_callback(const car_msgs::localization &localization){
    localization_ = localization;
}
void Controller::chassis_topic_callback(const car_msgs::chassis &chassis){
    chassis_ = chassis;
}

void Controller::path_topic_callback(const car_msgs::path_point &path_point){

}