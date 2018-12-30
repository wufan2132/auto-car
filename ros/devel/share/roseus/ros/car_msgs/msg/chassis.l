;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::chassis)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'chassis (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::CHASSIS")
  (make-package "CAR_MSGS::CHASSIS"))

(in-package "ROS")
;;//! \htmlinclude chassis.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::chassis
  :super ros::object
  :slots (_header _speed _acc ))

(defmethod car_msgs::chassis
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:speed __speed) (instance geometry_msgs::Vector3 :init))
    ((:acc __acc) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _speed __speed)
   (setq _acc __acc)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:speed
   (&rest __speed)
   (if (keywordp (car __speed))
       (send* _speed __speed)
     (progn
       (if __speed (setq _speed (car __speed)))
       _speed)))
  (:acc
   (&rest __acc)
   (if (keywordp (car __acc))
       (send* _acc __acc)
     (progn
       (if __acc (setq _acc (car __acc)))
       _acc)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Vector3 _speed
    (send _speed :serialization-length)
    ;; geometry_msgs/Vector3 _acc
    (send _acc :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Vector3 _speed
       (send _speed :serialize s)
     ;; geometry_msgs/Vector3 _acc
       (send _acc :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Vector3 _speed
     (send _speed :deserialize buf ptr-) (incf ptr- (send _speed :serialization-length))
   ;; geometry_msgs/Vector3 _acc
     (send _acc :deserialize buf ptr-) (incf ptr- (send _acc :serialization-length))
   ;;
   self)
  )

(setf (get car_msgs::chassis :md5sum-) "ce46c31b64d205e7445f8554a0115c6d")
(setf (get car_msgs::chassis :datatype-) "car_msgs/chassis")
(setf (get car_msgs::chassis :definition-)
      "Header header
geometry_msgs/Vector3 speed
geometry_msgs/Vector3 acc
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
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :car_msgs/chassis "ce46c31b64d205e7445f8554a0115c6d")


