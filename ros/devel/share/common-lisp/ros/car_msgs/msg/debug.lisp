; Auto-generated. Do not edit!


(cl:in-package car_msgs-msg)


;//! \htmlinclude debug.msg.html

(cl:defclass <debug> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (ts
    :reader ts
    :initarg :ts
    :type cl:float
    :initform 0.0)
   (lon_debug_msg
    :reader lon_debug_msg
    :initarg :lon_debug_msg
    :type car_msgs-msg:lon_debug
    :initform (cl:make-instance 'car_msgs-msg:lon_debug))
   (lat_debug_msg
    :reader lat_debug_msg
    :initarg :lat_debug_msg
    :type car_msgs-msg:lat_debug
    :initform (cl:make-instance 'car_msgs-msg:lat_debug))
   (mpc_debug_msg
    :reader mpc_debug_msg
    :initarg :mpc_debug_msg
    :type car_msgs-msg:mpc_debug
    :initform (cl:make-instance 'car_msgs-msg:mpc_debug)))
)

(cl:defclass debug (<debug>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <debug>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'debug)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car_msgs-msg:<debug> is deprecated: use car_msgs-msg:debug instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:header-val is deprecated.  Use car_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'ts-val :lambda-list '(m))
(cl:defmethod ts-val ((m <debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:ts-val is deprecated.  Use car_msgs-msg:ts instead.")
  (ts m))

(cl:ensure-generic-function 'lon_debug_msg-val :lambda-list '(m))
(cl:defmethod lon_debug_msg-val ((m <debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:lon_debug_msg-val is deprecated.  Use car_msgs-msg:lon_debug_msg instead.")
  (lon_debug_msg m))

(cl:ensure-generic-function 'lat_debug_msg-val :lambda-list '(m))
(cl:defmethod lat_debug_msg-val ((m <debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:lat_debug_msg-val is deprecated.  Use car_msgs-msg:lat_debug_msg instead.")
  (lat_debug_msg m))

(cl:ensure-generic-function 'mpc_debug_msg-val :lambda-list '(m))
(cl:defmethod mpc_debug_msg-val ((m <debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:mpc_debug_msg-val is deprecated.  Use car_msgs-msg:mpc_debug_msg instead.")
  (mpc_debug_msg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <debug>) ostream)
  "Serializes a message object of type '<debug>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ts))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'lon_debug_msg) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'lat_debug_msg) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'mpc_debug_msg) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <debug>) istream)
  "Deserializes a message object of type '<debug>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ts) (roslisp-utils:decode-double-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'lon_debug_msg) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'lat_debug_msg) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'mpc_debug_msg) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<debug>)))
  "Returns string type for a message object of type '<debug>"
  "car_msgs/debug")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'debug)))
  "Returns string type for a message object of type 'debug"
  "car_msgs/debug")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<debug>)))
  "Returns md5sum for a message object of type '<debug>"
  "a486330156a1499098fce50f1c4ae2b4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'debug)))
  "Returns md5sum for a message object of type 'debug"
  "a486330156a1499098fce50f1c4ae2b4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<debug>)))
  "Returns full string definition for message of type '<debug>"
  (cl:format cl:nil "Header header~%float64 ts~%lon_debug lon_debug_msg~%lat_debug lat_debug_msg~%mpc_debug mpc_debug_msg~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: car_msgs/lon_debug~%Header header~%~%float64 station_reference~%float64 station_error~%float64 station_error_limited~%float64 preview_station_error~%float64 station_out~%~%float64 speed_reference~%float64 speed_error~%float64 speed_controller_input_limited~%float64 preview_speed_reference~%float64 preview_speed_error~%float64 speed_out~%~%float64 preview_acceleration_reference~%float64 acceleration_cmd_closeloop~%float64 acceleration_cmd~%float64 acceleration_lookup~%float64 speed_lookup~%float64 calibration_value~%float64 throttle_cmd~%float64 brake_cmd~%bool is_full_stop~%float64 slope_offset_compensation~%float64 current_station~%float64 path_remain~%~%~%================================================================================~%MSG: car_msgs/lat_debug~%Header header~%~%float64 lateral_error~%float64 ref_heading~%float64 heading~%float64 heading_error~%float64 heading_error_rate~%float64 lateral_error_rate~%float64 curvature~%float64 steer_angle~%float64 steer_angle_feedforward~%float64 steer_angle_lateral_contribution~%float64 steer_angle_lateral_rate_contribution~%float64 steer_angle_heading_contribution~%float64 steer_angle_heading_rate_contribution~%float64 steer_angle_feedback~%float64 steering_position~%float64 ref_speed~%float64 steer_angle_limited~%================================================================================~%MSG: car_msgs/mpc_debug~%Header header~%~%float64 lateral_error~%float64 ref_heading~%float64 heading~%float64 heading_error~%float64 heading_error_rate~%float64 lateral_error_rate~%float64 curvature~%float64 steer_angle~%float64 steer_angle_feedforward~%float64 steer_angle_lateral_contribution~%float64 steer_angle_lateral_rate_contribution~%float64 steer_angle_heading_contribution~%float64 steer_angle_heading_rate_contribution~%float64 steer_angle_feedback~%float64 steering_position~%float64 ref_speed~%float64 steer_angle_limited~%float64 station_reference~%float64 station_error~%float64 speed_reference~%float64 speed_error~%float64 acceleration_reference~%bool is_full_stop~%float64 station_feedback~%float64 speed_feedback~%float64 acceleration_cmd_closeloop~%float64 acceleration_cmd~%float64 acceleration_lookup~%float64 speed_lookup~%float64 calibration_value~%float64 matrix_q_updated1     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated2     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated3     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated4     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated5     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated6     # matrix_q_updated_ size 6 repeated~%float64 matrix_r_updated1     # matrix_r_updated_ size 2  repeated~%float64 matrix_r_updated2     # matrix_r_updated_ size 2  repeated~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'debug)))
  "Returns full string definition for message of type 'debug"
  (cl:format cl:nil "Header header~%float64 ts~%lon_debug lon_debug_msg~%lat_debug lat_debug_msg~%mpc_debug mpc_debug_msg~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: car_msgs/lon_debug~%Header header~%~%float64 station_reference~%float64 station_error~%float64 station_error_limited~%float64 preview_station_error~%float64 station_out~%~%float64 speed_reference~%float64 speed_error~%float64 speed_controller_input_limited~%float64 preview_speed_reference~%float64 preview_speed_error~%float64 speed_out~%~%float64 preview_acceleration_reference~%float64 acceleration_cmd_closeloop~%float64 acceleration_cmd~%float64 acceleration_lookup~%float64 speed_lookup~%float64 calibration_value~%float64 throttle_cmd~%float64 brake_cmd~%bool is_full_stop~%float64 slope_offset_compensation~%float64 current_station~%float64 path_remain~%~%~%================================================================================~%MSG: car_msgs/lat_debug~%Header header~%~%float64 lateral_error~%float64 ref_heading~%float64 heading~%float64 heading_error~%float64 heading_error_rate~%float64 lateral_error_rate~%float64 curvature~%float64 steer_angle~%float64 steer_angle_feedforward~%float64 steer_angle_lateral_contribution~%float64 steer_angle_lateral_rate_contribution~%float64 steer_angle_heading_contribution~%float64 steer_angle_heading_rate_contribution~%float64 steer_angle_feedback~%float64 steering_position~%float64 ref_speed~%float64 steer_angle_limited~%================================================================================~%MSG: car_msgs/mpc_debug~%Header header~%~%float64 lateral_error~%float64 ref_heading~%float64 heading~%float64 heading_error~%float64 heading_error_rate~%float64 lateral_error_rate~%float64 curvature~%float64 steer_angle~%float64 steer_angle_feedforward~%float64 steer_angle_lateral_contribution~%float64 steer_angle_lateral_rate_contribution~%float64 steer_angle_heading_contribution~%float64 steer_angle_heading_rate_contribution~%float64 steer_angle_feedback~%float64 steering_position~%float64 ref_speed~%float64 steer_angle_limited~%float64 station_reference~%float64 station_error~%float64 speed_reference~%float64 speed_error~%float64 acceleration_reference~%bool is_full_stop~%float64 station_feedback~%float64 speed_feedback~%float64 acceleration_cmd_closeloop~%float64 acceleration_cmd~%float64 acceleration_lookup~%float64 speed_lookup~%float64 calibration_value~%float64 matrix_q_updated1     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated2     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated3     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated4     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated5     # matrix_q_updated_ size 6 repeated~%float64 matrix_q_updated6     # matrix_q_updated_ size 6 repeated~%float64 matrix_r_updated1     # matrix_r_updated_ size 2  repeated~%float64 matrix_r_updated2     # matrix_r_updated_ size 2  repeated~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <debug>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'lon_debug_msg))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'lat_debug_msg))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'mpc_debug_msg))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <debug>))
  "Converts a ROS message object to a list"
  (cl:list 'debug
    (cl:cons ':header (header msg))
    (cl:cons ':ts (ts msg))
    (cl:cons ':lon_debug_msg (lon_debug_msg msg))
    (cl:cons ':lat_debug_msg (lat_debug_msg msg))
    (cl:cons ':mpc_debug_msg (mpc_debug_msg msg))
))
