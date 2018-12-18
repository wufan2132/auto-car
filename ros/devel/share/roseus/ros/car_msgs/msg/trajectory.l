;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::trajectory)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'trajectory (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::TRAJECTORY")
  (make-package "CAR_MSGS::TRAJECTORY"))

(in-package "ROS")
;;//! \htmlinclude trajectory.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::trajectory
  :super ros::object
  :slots (_header _total_path_length _total_path_time _trajectory_path _absolute_time ))

(defmethod car_msgs::trajectory
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:total_path_length __total_path_length) 0.0)
    ((:total_path_time __total_path_time) 0.0)
    ((:trajectory_path __trajectory_path) (let (r) (dotimes (i 0) (push (instance car_msgs::trajectory_point :init) r)) r))
    ((:absolute_time __absolute_time) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _total_path_length (float __total_path_length))
   (setq _total_path_time (float __total_path_time))
   (setq _trajectory_path __trajectory_path)
   (setq _absolute_time (float __absolute_time))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:total_path_length
   (&optional __total_path_length)
   (if __total_path_length (setq _total_path_length __total_path_length)) _total_path_length)
  (:total_path_time
   (&optional __total_path_time)
   (if __total_path_time (setq _total_path_time __total_path_time)) _total_path_time)
  (:trajectory_path
   (&rest __trajectory_path)
   (if (keywordp (car __trajectory_path))
       (send* _trajectory_path __trajectory_path)
     (progn
       (if __trajectory_path (setq _trajectory_path (car __trajectory_path)))
       _trajectory_path)))
  (:absolute_time
   (&optional __absolute_time)
   (if __absolute_time (setq _absolute_time __absolute_time)) _absolute_time)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _total_path_length
    8
    ;; float64 _total_path_time
    8
    ;; car_msgs/trajectory_point[] _trajectory_path
    (apply #'+ (send-all _trajectory_path :serialization-length)) 4
    ;; float64 _absolute_time
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _total_path_length
       (sys::poke _total_path_length (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _total_path_time
       (sys::poke _total_path_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; car_msgs/trajectory_point[] _trajectory_path
     (write-long (length _trajectory_path) s)
     (dolist (elem _trajectory_path)
       (send elem :serialize s)
       )
     ;; float64 _absolute_time
       (sys::poke _absolute_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _total_path_length
     (setq _total_path_length (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _total_path_time
     (setq _total_path_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; car_msgs/trajectory_point[] _trajectory_path
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _trajectory_path (let (r) (dotimes (i n) (push (instance car_msgs::trajectory_point :init) r)) r))
     (dolist (elem- _trajectory_path)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float64 _absolute_time
     (setq _absolute_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get car_msgs::trajectory :md5sum-) "61de575059f17e8f9e68b40fc86fc888")
(setf (get car_msgs::trajectory :datatype-) "car_msgs/trajectory")
(setf (get car_msgs::trajectory :definition-)
      "Header header


float64 total_path_length
float64 total_path_time

trajectory_point[] trajectory_path

float64 absolute_time
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
MSG: car_msgs/trajectory_point
Header header

float64 x
float64 y
float64 z
float64 theta
float64 kappa
float64 s

float64 speed
float64 accel

float64 relative_time
")



(provide :car_msgs/trajectory "61de575059f17e8f9e68b40fc86fc888")


