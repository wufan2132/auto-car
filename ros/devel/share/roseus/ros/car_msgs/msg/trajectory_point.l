;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::trajectory_point)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'trajectory_point (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::TRAJECTORY_POINT")
  (make-package "CAR_MSGS::TRAJECTORY_POINT"))

(in-package "ROS")
;;//! \htmlinclude trajectory_point.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::trajectory_point
  :super ros::object
  :slots (_header _x _y _z _theta _kappa _s _speed _accel _relative_time ))

(defmethod car_msgs::trajectory_point
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:theta __theta) 0.0)
    ((:kappa __kappa) 0.0)
    ((:s __s) 0.0)
    ((:speed __speed) 0.0)
    ((:accel __accel) 0.0)
    ((:relative_time __relative_time) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _theta (float __theta))
   (setq _kappa (float __kappa))
   (setq _s (float __s))
   (setq _speed (float __speed))
   (setq _accel (float __accel))
   (setq _relative_time (float __relative_time))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:kappa
   (&optional __kappa)
   (if __kappa (setq _kappa __kappa)) _kappa)
  (:s
   (&optional __s)
   (if __s (setq _s __s)) _s)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:accel
   (&optional __accel)
   (if __accel (setq _accel __accel)) _accel)
  (:relative_time
   (&optional __relative_time)
   (if __relative_time (setq _relative_time __relative_time)) _relative_time)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _theta
    8
    ;; float64 _kappa
    8
    ;; float64 _s
    8
    ;; float64 _speed
    8
    ;; float64 _accel
    8
    ;; float64 _relative_time
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _kappa
       (sys::poke _kappa (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _s
       (sys::poke _s (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _accel
       (sys::poke _accel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _relative_time
       (sys::poke _relative_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta
     (setq _theta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _kappa
     (setq _kappa (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _s
     (setq _s (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed
     (setq _speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _accel
     (setq _accel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _relative_time
     (setq _relative_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get car_msgs::trajectory_point :md5sum-) "5e311e54de4ba9856b316e2cfa921066")
(setf (get car_msgs::trajectory_point :datatype-) "car_msgs/trajectory_point")
(setf (get car_msgs::trajectory_point :definition-)
      "Header header

float64 x
float64 y
float64 z
float64 theta
float64 kappa
float64 s

float64 speed
float64 accel

float64 relative_time
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

")



(provide :car_msgs/trajectory_point "5e311e54de4ba9856b316e2cfa921066")


