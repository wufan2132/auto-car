;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::debug)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'debug (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::DEBUG")
  (make-package "CAR_MSGS::DEBUG"))

(in-package "ROS")
;;//! \htmlinclude debug.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::debug
  :super ros::object
  :slots (_header _ts _lon_debug_msg _lat_debug_msg _mpc_debug_msg ))

(defmethod car_msgs::debug
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:ts __ts) 0.0)
    ((:lon_debug_msg __lon_debug_msg) (instance car_msgs::lon_debug :init))
    ((:lat_debug_msg __lat_debug_msg) (instance car_msgs::lat_debug :init))
    ((:mpc_debug_msg __mpc_debug_msg) (instance car_msgs::mpc_debug :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _ts (float __ts))
   (setq _lon_debug_msg __lon_debug_msg)
   (setq _lat_debug_msg __lat_debug_msg)
   (setq _mpc_debug_msg __mpc_debug_msg)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:ts
   (&optional __ts)
   (if __ts (setq _ts __ts)) _ts)
  (:lon_debug_msg
   (&rest __lon_debug_msg)
   (if (keywordp (car __lon_debug_msg))
       (send* _lon_debug_msg __lon_debug_msg)
     (progn
       (if __lon_debug_msg (setq _lon_debug_msg (car __lon_debug_msg)))
       _lon_debug_msg)))
  (:lat_debug_msg
   (&rest __lat_debug_msg)
   (if (keywordp (car __lat_debug_msg))
       (send* _lat_debug_msg __lat_debug_msg)
     (progn
       (if __lat_debug_msg (setq _lat_debug_msg (car __lat_debug_msg)))
       _lat_debug_msg)))
  (:mpc_debug_msg
   (&rest __mpc_debug_msg)
   (if (keywordp (car __mpc_debug_msg))
       (send* _mpc_debug_msg __mpc_debug_msg)
     (progn
       (if __mpc_debug_msg (setq _mpc_debug_msg (car __mpc_debug_msg)))
       _mpc_debug_msg)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _ts
    8
    ;; car_msgs/lon_debug _lon_debug_msg
    (send _lon_debug_msg :serialization-length)
    ;; car_msgs/lat_debug _lat_debug_msg
    (send _lat_debug_msg :serialization-length)
    ;; car_msgs/mpc_debug _mpc_debug_msg
    (send _mpc_debug_msg :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _ts
       (sys::poke _ts (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; car_msgs/lon_debug _lon_debug_msg
       (send _lon_debug_msg :serialize s)
     ;; car_msgs/lat_debug _lat_debug_msg
       (send _lat_debug_msg :serialize s)
     ;; car_msgs/mpc_debug _mpc_debug_msg
       (send _mpc_debug_msg :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _ts
     (setq _ts (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; car_msgs/lon_debug _lon_debug_msg
     (send _lon_debug_msg :deserialize buf ptr-) (incf ptr- (send _lon_debug_msg :serialization-length))
   ;; car_msgs/lat_debug _lat_debug_msg
     (send _lat_debug_msg :deserialize buf ptr-) (incf ptr- (send _lat_debug_msg :serialization-length))
   ;; car_msgs/mpc_debug _mpc_debug_msg
     (send _mpc_debug_msg :deserialize buf ptr-) (incf ptr- (send _mpc_debug_msg :serialization-length))
   ;;
   self)
  )

(setf (get car_msgs::debug :md5sum-) "a486330156a1499098fce50f1c4ae2b4")
(setf (get car_msgs::debug :datatype-) "car_msgs/debug")
(setf (get car_msgs::debug :definition-)
      "Header header
float64 ts
lon_debug lon_debug_msg
lat_debug lat_debug_msg
mpc_debug mpc_debug_msg
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: car_msgs/lon_debug
Header header

float64 station_reference
float64 station_error
float64 station_error_limited
float64 preview_station_error
float64 station_out

float64 speed_reference
float64 speed_error
float64 speed_controller_input_limited
float64 preview_speed_reference
float64 preview_speed_error
float64 speed_out

float64 preview_acceleration_reference
float64 acceleration_cmd_closeloop
float64 acceleration_cmd
float64 acceleration_lookup
float64 speed_lookup
float64 calibration_value
float64 throttle_cmd
float64 brake_cmd
bool is_full_stop
float64 slope_offset_compensation
float64 current_station
float64 path_remain


================================================================================
MSG: car_msgs/lat_debug
Header header

float64 lateral_error
float64 ref_heading
float64 heading
float64 heading_error
float64 heading_error_rate
float64 lateral_error_rate
float64 curvature
float64 steer_angle
float64 steer_angle_feedforward
float64 steer_angle_lateral_contribution
float64 steer_angle_lateral_rate_contribution
float64 steer_angle_heading_contribution
float64 steer_angle_heading_rate_contribution
float64 steer_angle_feedback
float64 steering_position
float64 ref_speed
float64 steer_angle_limited
================================================================================
MSG: car_msgs/mpc_debug
Header header

float64 lateral_error
float64 ref_heading
float64 heading
float64 heading_error
float64 heading_error_rate
float64 lateral_error_rate
float64 curvature
float64 steer_angle
float64 steer_angle_feedforward
float64 steer_angle_lateral_contribution
float64 steer_angle_lateral_rate_contribution
float64 steer_angle_heading_contribution
float64 steer_angle_heading_rate_contribution
float64 steer_angle_feedback
float64 steering_position
float64 ref_speed
float64 steer_angle_limited
float64 station_reference
float64 station_error
float64 speed_reference
float64 speed_error
float64 acceleration_reference
bool is_full_stop
float64 station_feedback
float64 speed_feedback
float64 acceleration_cmd_closeloop
float64 acceleration_cmd
float64 acceleration_lookup
float64 speed_lookup
float64 calibration_value
float64 matrix_q_updated1     # matrix_q_updated_ size 6 repeated
float64 matrix_q_updated2     # matrix_q_updated_ size 6 repeated
float64 matrix_q_updated3     # matrix_q_updated_ size 6 repeated
float64 matrix_q_updated4     # matrix_q_updated_ size 6 repeated
float64 matrix_q_updated5     # matrix_q_updated_ size 6 repeated
float64 matrix_q_updated6     # matrix_q_updated_ size 6 repeated
float64 matrix_r_updated1     # matrix_r_updated_ size 2  repeated
float64 matrix_r_updated2     # matrix_r_updated_ size 2  repeated
")



(provide :car_msgs/debug "a486330156a1499098fce50f1c4ae2b4")


