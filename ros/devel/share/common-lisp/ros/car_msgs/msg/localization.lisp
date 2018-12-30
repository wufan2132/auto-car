; Auto-generated. Do not edit!


(cl:in-package car_msgs-msg)


;//! \htmlinclude localization.msg.html

(cl:defclass <localization> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (angle
    :reader angle
    :initarg :angle
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (angular_velocity
    :reader angular_velocity
    :initarg :angular_velocity
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass localization (<localization>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <localization>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'localization)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car_msgs-msg:<localization> is deprecated: use car_msgs-msg:localization instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <localization>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:header-val is deprecated.  Use car_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <localization>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:position-val is deprecated.  Use car_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <localization>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:angle-val is deprecated.  Use car_msgs-msg:angle instead.")
  (angle m))

(cl:ensure-generic-function 'angular_velocity-val :lambda-list '(m))
(cl:defmethod angular_velocity-val ((m <localization>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_msgs-msg:angular_velocity-val is deprecated.  Use car_msgs-msg:angular_velocity instead.")
  (angular_velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <localization>) ostream)
  "Serializes a message object of type '<localization>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angle) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angular_velocity) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <localization>) istream)
  "Deserializes a message object of type '<localization>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angle) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angular_velocity) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<localization>)))
  "Returns string type for a message object of type '<localization>"
  "car_msgs/localization")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'localization)))
  "Returns string type for a message object of type 'localization"
  "car_msgs/localization")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<localization>)))
  "Returns md5sum for a message object of type '<localization>"
  "f8b2c5bd77f4ae6f1a47d22a99bc4654")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'localization)))
  "Returns md5sum for a message object of type 'localization"
  "f8b2c5bd77f4ae6f1a47d22a99bc4654")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<localization>)))
  "Returns full string definition for message of type '<localization>"
  (cl:format cl:nil "Header header~%geometry_msgs/Point position~%geometry_msgs/Vector3 angle~%geometry_msgs/Vector3 angular_velocity~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'localization)))
  "Returns full string definition for message of type 'localization"
  (cl:format cl:nil "Header header~%geometry_msgs/Point position~%geometry_msgs/Vector3 angle~%geometry_msgs/Vector3 angular_velocity~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <localization>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angle))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angular_velocity))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <localization>))
  "Converts a ROS message object to a list"
  (cl:list 'localization
    (cl:cons ':header (header msg))
    (cl:cons ':position (position msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':angular_velocity (angular_velocity msg))
))
