#include "control/controller.h"
#include "yaml-cpp/yaml.h"
#define LON_CONTROLLER_CONF_DIR "src/control/src/conf/control.yaml"
using namespace std;

Controller::Controller(void){
    Init();
}

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
    lon_controller_conf.station_pid_conf.output_saturation_level = controller_conf["lon_controller_conf"]["output_saturation_level"]["kp"].as<double>();

    lon_controller_conf.station_pid_conf.integrator_enable = controller_conf["lon_controller_conf"]["speed_pid_conf"]["integrator_enable"].as<bool>();
    lon_controller_conf.station_pid_conf.integrator_saturation_level = controller_conf["lon_controller_conf"]["speed_pid_conf"]["integrator_saturation_level"].as<double>();
    lon_controller_conf.station_pid_conf.kp = controller_conf["lon_controller_conf"]["speed_pid_conf"]["kp"].as<double>();
    lon_controller_conf.station_pid_conf.ki = controller_conf["lon_controller_conf"]["speed_pid_conf"]["ki"].as<double>();
    lon_controller_conf.station_pid_conf.kd = controller_conf["lon_controller_conf"]["speed_pid_conf"]["kd"].as<double>();
    lon_controller_conf.station_pid_conf.kaw = controller_conf["lon_controller_conf"]["speed_pid_conf"]["kaw"].as<double>();
    lon_controller_conf.station_pid_conf.output_saturation_level = controller_conf["speed_pid_conf"]["output_saturation_level"]["kp"].as<double>();
    
    lon_controller_.Init(&lon_controller_conf);
}

void Controller::ProduceControlCommand(msgs::chassisCommand *cmd){

    lon_controller_.ComputeControlCommand(&localization_,&chassis_,&trajectory_,cmd);
}

void Controller::CheckInput(void){

}

void Controller::SendCmd(msgs::chassisCommand *cmd){

}

void Controller::OnTimer(void){

}