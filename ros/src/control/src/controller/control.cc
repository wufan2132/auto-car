#include "control/control.h"
#include "yaml-cpp/yaml.h"
#define CONTROL_CONF_DIR "../my-code/auto-car/ros/src/control/src/conf/control.yaml"

namespace control {
using namespace std;

void Control::Init(void){
    YAML::Node control_conf = YAML::LoadFile(CONTROL_CONF_DIR);


//模式参数
    control_mode_ = control_conf["control_mode"].as<int>();
    debug_mode_ = control_conf["debug_mode"].as<int>();
#if MPC_OR_LQR
    LonControllerConf lon_controller_conf;
    LatControllerConf lat_controller_conf;
//配置纵向控制参数
    lon_controller_conf.ts                                           = control_conf["lon_controller_conf"]["ts"].as<double>();
    lon_controller_conf.station_pid_conf.integrator_enable           = control_conf["lon_controller_conf"]["station_pid_conf"]["integrator_enable"].as<bool>();
    lon_controller_conf.station_pid_conf.integrator_saturation_level = control_conf["lon_controller_conf"]["station_pid_conf"]["integrator_saturation_level"].as<double>();
    lon_controller_conf.station_pid_conf.kp                          = control_conf["lon_controller_conf"]["station_pid_conf"]["kp"].as<double>();
    lon_controller_conf.station_pid_conf.ki                          = control_conf["lon_controller_conf"]["station_pid_conf"]["ki"].as<double>();
    lon_controller_conf.station_pid_conf.kd                          = control_conf["lon_controller_conf"]["station_pid_conf"]["kd"].as<double>();
    lon_controller_conf.station_pid_conf.kaw                         = control_conf["lon_controller_conf"]["station_pid_conf"]["kaw"].as<double>();
    lon_controller_conf.station_pid_conf.output_saturation_level     = control_conf["lon_controller_conf"]["station_pid_conf"]["output_saturation_level"].as<double>();

    lon_controller_conf.speed_pid_conf.integrator_enable           = control_conf["lon_controller_conf"]["speed_pid_conf"]["integrator_enable"].as<bool>();
    lon_controller_conf.speed_pid_conf.integrator_saturation_level = control_conf["lon_controller_conf"]["speed_pid_conf"]["integrator_saturation_level"].as<double>();
    lon_controller_conf.speed_pid_conf.kp                          = control_conf["lon_controller_conf"]["speed_pid_conf"]["kp"].as<double>();
    lon_controller_conf.speed_pid_conf.ki                          = control_conf["lon_controller_conf"]["speed_pid_conf"]["ki"].as<double>();
    lon_controller_conf.speed_pid_conf.kd                          = control_conf["lon_controller_conf"]["speed_pid_conf"]["kd"].as<double>();
    lon_controller_conf.speed_pid_conf.kaw                         = control_conf["lon_controller_conf"]["speed_pid_conf"]["kaw"].as<double>();
    lon_controller_conf.speed_pid_conf.output_saturation_level     = control_conf["lon_controller_conf"]["speed_pid_conf"]["output_saturation_level"].as<double>();
    
    lon_controller_.Init(&lon_controller_conf);
//配置横向控制参数
    lat_controller_conf.query_relative_time      = control_conf["query_relative_time"].as<double>();
    lat_controller_conf.minimum_speed_protection = control_conf["minimum_speed_protection"].as<double>();

    lat_controller_conf.ts                       = control_conf["lat_controller_conf"]["ts"].as<double>();
    lat_controller_conf.preview_window           = control_conf["lat_controller_conf"]["preview_window"].as<int>();
    lat_controller_conf.cf                       = control_conf["lat_controller_conf"]["cf"].as<double>();
    lat_controller_conf.cr                       = control_conf["lat_controller_conf"]["cr"].as<double>();
    lat_controller_conf.mass_fl                  = control_conf["lat_controller_conf"]["mass_fl"].as<int>();
    lat_controller_conf.mass_fr                  = control_conf["lat_controller_conf"]["mass_fr"].as<int>();
    lat_controller_conf.mass_rl                  = control_conf["lat_controller_conf"]["mass_rl"].as<int>();
    lat_controller_conf.mass_rr                  = control_conf["lat_controller_conf"]["mass_rr"].as<int>();
    lat_controller_conf.eps                      = control_conf["lat_controller_conf"]["eps"].as<double>();
    lat_controller_conf.matrix_q1                = control_conf["lat_controller_conf"]["matrix_q1"].as<double>();
    lat_controller_conf.matrix_q2                = control_conf["lat_controller_conf"]["matrix_q2"].as<double>();
    lat_controller_conf.matrix_q3                = control_conf["lat_controller_conf"]["matrix_q3"].as<double>();
    lat_controller_conf.matrix_q4                = control_conf["lat_controller_conf"]["matrix_q4"].as<double>();
    lat_controller_conf.cutoff_freq              = control_conf["lat_controller_conf"]["cutoff_freq"].as<int>();
    lat_controller_conf.mean_filter_window_size  = control_conf["lat_controller_conf"]["mean_filter_window_size"].as<int>();
    lat_controller_conf.max_iteration            = control_conf["lat_controller_conf"]["max_iteration"].as<int>();
    lat_controller_conf.max_lateral_acceleration = control_conf["lat_controller_conf"]["max_lateral_acceleration"].as<double>();

    lat_controller_conf.front_edge_to_center = control_conf["vehicle_param"]["front_edge_to_center"].as<double>();
    lat_controller_conf.back_edge_to_center  = control_conf["vehicle_param"]["back_edge_to_center"].as<double>();
    lat_controller_conf.left_edge_to_center  = control_conf["vehicle_param"]["left_edge_to_center"].as<double>();
    lat_controller_conf.right_edge_to_center = control_conf["vehicle_param"]["right_edge_to_center"].as<double>();
    lat_controller_conf.length               = control_conf["vehicle_param"]["length"].as<double>();
    lat_controller_conf.width                = control_conf["vehicle_param"]["width"].as<double>();
    lat_controller_conf.height               = control_conf["vehicle_param"]["height"].as<double>();
    lat_controller_conf.min_turn_radius      = control_conf["vehicle_param"]["min_turn_radius"].as<double>();
    lat_controller_conf.max_acceleration     = control_conf["vehicle_param"]["max_acceleration"].as<double>();
    lat_controller_conf.max_deceleration     = control_conf["vehicle_param"]["max_deceleration"].as<double>();
    lat_controller_conf.max_steer_angle      = control_conf["vehicle_param"]["max_steer_angle"].as<double>();
    lat_controller_conf.max_steer_angle_rate = control_conf["vehicle_param"]["max_steer_angle_rate"].as<double>();
    // lat_controller_conf.min_steer_angle_rate = control_conf["vehicle_param"]["min_steer_angle_rate"].as<double>();
    lat_controller_conf.steer_ratio          = control_conf["vehicle_param"]["steer_ratio"].as<double>();
    lat_controller_conf.wheel_base           = control_conf["vehicle_param"]["wheel_base"].as<double>();
    lat_controller_conf.wheel_rolling_radius = control_conf["vehicle_param"]["wheel_rolling_radius"].as<double>();
    //lat_controller_conf.max_abs_speed_when_stopped = control_conf["vehicle_param"]["max_abs_speed_when_stopped"].as<float>();

    lat_controller_.Init(&lat_controller_conf);
#else
    MPCControllerConf mpc_controller_conf;
//配置mpc参数
    mpc_controller_conf.ts                       = control_conf["mpc_controller_conf"]["ts"].as<double>();
    mpc_controller_conf.cf                       = control_conf["mpc_controller_conf"]["cf"].as<double>();
    mpc_controller_conf.cr                       = control_conf["mpc_controller_conf"]["cr"].as<double>();
    mpc_controller_conf.mass_fl                  = control_conf["mpc_controller_conf"]["mass_fl"].as<int>();
    mpc_controller_conf.mass_fr                  = control_conf["mpc_controller_conf"]["mass_fr"].as<int>();
    mpc_controller_conf.mass_rl                  = control_conf["mpc_controller_conf"]["mass_rl"].as<int>();
    mpc_controller_conf.mass_rr                  = control_conf["mpc_controller_conf"]["mass_rr"].as<int>();
    mpc_controller_conf.eps                      = control_conf["mpc_controller_conf"]["eps"].as<double>();
    mpc_controller_conf.matrix_q1                = control_conf["mpc_controller_conf"]["matrix_q1"].as<double>();
    mpc_controller_conf.matrix_q2                = control_conf["mpc_controller_conf"]["matrix_q2"].as<double>();
    mpc_controller_conf.matrix_q3                = control_conf["mpc_controller_conf"]["matrix_q3"].as<double>();
    mpc_controller_conf.matrix_q4                = control_conf["mpc_controller_conf"]["matrix_q4"].as<double>();
    mpc_controller_conf.matrix_q5                = control_conf["mpc_controller_conf"]["matrix_q5"].as<double>();
    mpc_controller_conf.matrix_q6                = control_conf["mpc_controller_conf"]["matrix_q6"].as<double>();
    mpc_controller_conf.matrix_r1                = control_conf["mpc_controller_conf"]["matrix_r1"].as<double>();
    mpc_controller_conf.matrix_r2                = control_conf["mpc_controller_conf"]["matrix_r2"].as<double>();
    mpc_controller_conf.cutoff_freq              = control_conf["mpc_controller_conf"]["cutoff_freq"].as<int>();
    mpc_controller_conf.mean_filter_window_size  = control_conf["mpc_controller_conf"]["mean_filter_window_size"].as<int>();
    mpc_controller_conf.max_iteration            = control_conf["mpc_controller_conf"]["max_iteration"].as<int>();
    mpc_controller_conf.max_lateral_acceleration = control_conf["mpc_controller_conf"]["max_lateral_acceleration"].as<double>();
    mpc_controller_conf.standstill_acceleration     = control_conf["mpc_controller_conf"]["standstill_acceleration"].as<double>();
    mpc_controller_conf.throttle_deadzone           = control_conf["mpc_controller_conf"]["throttle_deadzone"].as<double>();
    mpc_controller_conf.brake_deadzone              = control_conf["mpc_controller_conf"]["brake_deadzone"].as<double>();
    mpc_controller_conf.minimum_speed_protection        = control_conf["minimum_speed_protection"].as<double>();

    mpc_controller_conf.front_edge_to_center = control_conf["vehicle_param"]["front_edge_to_center"].as<double>();
    mpc_controller_conf.back_edge_to_center  = control_conf["vehicle_param"]["back_edge_to_center"].as<double>();
    mpc_controller_conf.left_edge_to_center  = control_conf["vehicle_param"]["left_edge_to_center"].as<double>();
    mpc_controller_conf.right_edge_to_center = control_conf["vehicle_param"]["right_edge_to_center"].as<double>();
    mpc_controller_conf.length               = control_conf["vehicle_param"]["length"].as<double>();
    mpc_controller_conf.width                = control_conf["vehicle_param"]["width"].as<double>();
    mpc_controller_conf.height               = control_conf["vehicle_param"]["height"].as<double>();
    mpc_controller_conf.min_turn_radius      = control_conf["vehicle_param"]["min_turn_radius"].as<double>();
    mpc_controller_conf.max_acceleration     = control_conf["vehicle_param"]["max_acceleration"].as<double>();
    mpc_controller_conf.max_deceleration     = control_conf["vehicle_param"]["max_deceleration"].as<double>();
    mpc_controller_conf.max_steer_angle      = control_conf["vehicle_param"]["max_steer_angle"].as<double>();
    mpc_controller_conf.max_steer_angle_rate = control_conf["vehicle_param"]["max_steer_angle_rate"].as<double>();
    // mpc_controller_conf.min_steer_angle_rate = control_conf["vehicle_param"]["min_steer_angle_rate"].as<double>();
    mpc_controller_conf.steer_ratio          = control_conf["vehicle_param"]["steer_ratio"].as<double>();
    mpc_controller_conf.wheel_base           = control_conf["vehicle_param"]["wheel_base"].as<double>();
    mpc_controller_conf.wheel_rolling_radius = control_conf["vehicle_param"]["wheel_rolling_radius"].as<double>();
    
    mpc_controller_.Init(&mpc_controller_conf);
#endif
//发布控制节点
    chassisCommand_publisher = control_NodeHandle.advertise<car_msgs::control_cmd>("prius", 1);
    debug_publisher = control_NodeHandle.advertise<car_msgs::debug>("debug", 1);
}

void Control::ProduceControlCommand(car_msgs::control_cmd &control_cmd){
#if MPC_OR_LQR
    lon_controller_.ComputeControlCommand(trajectory_path_,vehicle_state_,control_cmd,debug_.lon_debug_msg);

    lat_controller_.ComputeControlCommand(trajectory_path_,vehicle_state_,control_cmd,debug_.lat_debug_msg);
#else
    mpc_controller_.ComputeControlCommand(trajectory_path_,vehicle_state_,control_cmd,debug_.mpc_debug_msg);
#endif
}

bool Control::CheckInput(void){

    vehicle_state_.x                = localization_.position.x;
    vehicle_state_.y                = localization_.position.y;
    vehicle_state_.z                = localization_.position.z;
    vehicle_state_.roll             = localization_.angle.x;
    vehicle_state_.pitch            = localization_.angle.y;
    vehicle_state_.yaw              = localization_.angle.z;
    vehicle_state_.heading          = localization_.angle.z;
    vehicle_state_.angular_velocity = localization_.angular_velocity.z;
    vehicle_state_.linear_velocity  = chassis_.speed.x;

    if(trajectory_path_.trajectory_path.size() == 0){
        return false;
    }else{
        return true;
    }
}

void Control::SendCmd(car_msgs::control_cmd &control_cmd){
    if(control_mode_ == 0){
        control_cmd.header = localization_.header;
        chassisCommand_publisher.publish(control_cmd);
    }
}

void Control::Debug(void){
    static double time_now = 0,time_old = 0;
    time_now = ros::Time::now().toSec();
    debug_.ts = (time_now - trajectory_path_.absolute_time)* 1000;
    //ROS_INFO("time_now:%f   trajectory_path_.absolute_time:%f",time_now,trajectory_path_.absolute_time);
    time_old = time_now;

    if(debug_mode_ == 1){
        debug_.header = localization_.header;
        debug_publisher.publish(debug_);
    }
}

void Control::OnTimer(const ros::TimerEvent&){
    static bool isdataNone = 0;
    car_msgs:: control_cmd control_cmd;

    if(!CheckInput()){
        if(isdataNone == 0){
            ROS_WARN("Control::OnTimer: trajectory is null!");
            isdataNone = 1;
        }
        return;
    }
    isdataNone = 0;
    ProduceControlCommand(control_cmd);
    SendCmd(control_cmd);
    Debug();
}

void Control::localization_topic_callback(const car_msgs::localization &localization){
    localization_ = localization;
}
void Control::chassis_topic_callback(const car_msgs::chassis &chassis){
    chassis_ = chassis;
}

void Control::path_topic_callback(const car_msgs::trajectory &trajectory_path){
    trajectory_path_ = trajectory_path;
}
}
