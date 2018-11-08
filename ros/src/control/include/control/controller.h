#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class VehicleState {
    public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double timestamp = 0.0;
    double roll = 0.0;
    double pitch = 0.0;
    double yaw = 0.0;
    double heading = 0.0;
    double kappa = 0.0;
    double linear_velocity = 0.0;
    double angular_velocity = 0.0;
    double linear_acceleration = 0.0;
};

class SimpleLongitudinalDebug {
    public:
    double station_reference;
    double station_error;
    double station_error_limited;
    double preview_station_error;
    double speed_reference;
    double speed_error;
    double speed_controller_input_limited;
    double preview_speed_reference;
    double preview_speed_error;
    double preview_acceleration_reference;
    double acceleration_cmd_closeloop;
    double acceleration_cmd;
    double acceleration_lookup;
    double speed_lookup;
    double calibration_value;
    double throttle_cmd;
    double brake_cmd;
    bool is_full_stop;
    double slope_offset_compensation;
    double current_station;
    double path_remain;
};

class SimpleLateralDebug {
    public:
    double lateral_error;
    double ref_heading;
    double heading;
    double heading_error;
    double heading_error_rate;
    double lateral_error_rate;
    double curvature;
    double steer_angle;
    double steer_angle_feedforward;
    double steer_angle_lateral_contribution;
    double steer_angle_lateral_rate_contribution;
    double steer_angle_heading_contribution;
    double steer_angle_heading_rate_contribution;
    double steer_angle_feedback;
    double steering_position;
    double ref_speed;
    double steer_angle_limited;
};

class SimpleMPCDebug {
    public:
    double lateral_error;
    double ref_heading;
    double heading;
    double heading_error;
    double heading_error_rate;
    double lateral_error_rate;
    double curvature;
    double steer_angle;
    double steer_angle_feedforward;
    double steer_angle_lateral_contribution;
    double steer_angle_lateral_rate_contribution;
    double steer_angle_heading_contribution;
    double steer_angle_heading_rate_contribution;
    double steer_angle_feedback;
    double steering_position;
    double ref_speed;
    double steer_angle_limited;
    double station_reference;
    double station_error;
    double speed_reference;
    double speed_error;
    double acceleration_reference;
    bool is_full_stop;
    double station_feedback;
    double speed_feedback;
    double acceleration_cmd_closeloop;
    double acceleration_cmd;
    double acceleration_lookup;
    double speed_lookup;
    double calibration_value;
   double matrix_q_updated;     // matrix_q_updated_ size 6 repeated
   double matrix_r_updated;    // matrix_r_updated_ size 2  repeated
};

class InputDebug {
    public:
    double localization_header;
    double canbus_header;
    double trajectory_header;
};

class Debug {
    public:
    SimpleLongitudinalDebug simple_lon_debug;
    SimpleLateralDebug simple_lat_debug;
    InputDebug input_debug;
    SimpleMPCDebug simple_mpc_debug;
};

#endif   //_CONTROLLER_H_