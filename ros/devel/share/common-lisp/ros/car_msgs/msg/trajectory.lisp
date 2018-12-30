; Auto-generated. Do not edit!


(cl:in-package car_msgs-msg)


;//! \htmlinclude trajectory.msg.html

(cl:defclass <trajectory> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (total_path_length
    :reader total_path_length
    :initarg :total_path_length
    :type cl:float
    :initform 0.0)
   (total_path_time
    :reader total_path_time
    :initarg :total_path_time
    :type cl:float
    :initform 0.0)
   (trajectory_path
    :reader trajectory_path
    :initarg :trajectory_path
    :type (cl:vector car_msgs-msg:trajectory_point)
   :initform (cl:make-array 0 :element-type 'car_msgs-msg:trajectory_point :initial-element (cl:make-instance 'car_msgs-msg:trajectory_point)))
   (absolute_time
    :reader absolute_time
    :initarg :absolute_time
    :type cl:float
    :initform 0.0))
)

(cl:defclass trajectory (<trajectory>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <trajectory>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'trajectory)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car_msgs-msg:<trajectory> is deprecated: use car_msgs-msg:trajectory instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:header-val is deprecated.  Use car_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'total_path_length-val :lambda-list '(m))
(cl:defmethod total_path_length-val ((m <trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:total_path_length-val is deprecated.  Use car_msgs-msg:total_path_length instead.")
  (total_path_length m))

(cl:ensure-generic-function 'total_path_time-val :lambda-list '(m))
(cl:defmethod total_path_time-val ((m <trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:total_path_time-val is deprecated.  Use car_msgs-msg:total_path_time instead.")
  (total_path_time m))

(cl:ensure-generic-function 'trajectory_path-val :lambda-list '(m))
(cl:defmethod trajectory_path-val ((m <trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:trajectory_path-val is deprecated.  Use car_msgs-msg:trajectory_path instead.")
  (trajectory_path m))

(cl:ensure-generic-function 'absolute_time-val :lambda-list '(m))
(cl:defmethod absolute_time-val ((m <trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:absolute_time-val is deprecated.  Use car_msgs-msg:absolute_time instead.")
  (absolute_time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <trajectory>) ostream)
  "Serializes a message object of type '<trajectory>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'total_path_length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'total_path_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'trajectory_path))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'trajectory_path))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'absolute_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <trajectory>) istream)
  "Deserializes a message object of type '<trajectory>"
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
    (cl:setf (cl:slot-value msg 'total_path_length) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'total_path_time) (roslisp-utils:decode-double-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'trajectory_path) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'trajectory_path)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'car_msgs-msg:trajectory_point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'absolute_time) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<trajectory>)))
  "Returns string type for a message object of type '<trajectory>"
  "car_msgs/trajectory")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'trajectory)))
  "Returns string type for a message object of type 'trajectory"
  "car_msgs/trajectory")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<trajectory>)))
  "Returns md5sum for a message object of type '<trajectory>"
  "61de575059f17e8f9e68b40fc86fc888")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'trajectory)))
  "Returns md5sum for a message object of type 'trajectory"
  "61de575059f17e8f9e68b40fc86fc888")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<trajectory>)))
  "Returns full string definition for message of type '<trajectory>"
  (cl:format cl:nil "Header header~%~%~%float64 total_path_length~%float64 total_path_time~%~%trajectory_point[] trajectory_path~%~%float64 absolute_time~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: car_msgs/trajectory_point~%Header header~%~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%~%float64 speed~%float64 accel~%~%float64 relative_time~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'trajectory)))
  "Returns full string definition for message of type 'trajectory"
  (cl:format cl:nil "Header header~%~%~%float64 total_path_length~%float64 total_path_time~%~%trajectory_point[] trajectory_path~%~%float64 absolute_time~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: car_msgs/trajectory_point~%Header header~%~%float64 x~%float64 y~%float64 z~%float64 theta~%float64 kappa~%float64 s~%~%float64 speed~%float64 accel~%~%float64 relative_time~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <trajectory>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'trajectory_path) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <trajectory>))
  "Converts a ROS message object to a list"
  (cl:list 'trajectory
    (cl:cons ':header (header msg))
    (cl:cons ':total_path_length (total_path_length msg))
    (cl:cons ':total_path_time (total_path_time msg))
    (cl:cons ':trajectory_path (trajectory_path msg))
    (cl:cons ':absolute_time (absolute_time msg))
))
