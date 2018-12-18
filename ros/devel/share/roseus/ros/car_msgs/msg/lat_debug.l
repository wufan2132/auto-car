;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::lat_debug)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'lat_debug (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::LAT_DEBUG")
  (make-package "CAR_MSGS::LAT_DEBUG"))

(in-package "ROS")
;;//! \htmlinclude lat_debug.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::lat_debug
  :super ros::object
  :slots (_header _lateral_error _ref_heading _heading _heading_error _heading_error_rate _lateral_error_rate _curvature _steer_angle _steer_angle_feedforward _steer_angle_lateral_contribution _steer_angle_lateral_rate_contribution _steer_angle_heading_contribution _steer_angle_heading_rate_contribution _steer_angle_feedback _steering_position _ref_speed _steer_angle_limited ))

(defmethod car_msgs::lat_debug
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lateral_error __lateral_error) 0.0)
    ((:ref_heading __ref_heading) 0.0)
    ((:heading __heading) 0.0)
    ((:heading_error __heading_error) 0.0)
    ((:heading_error_rate __heading_error_rate) 0.0)
    ((:lateral_error_rate __lateral_error_rate) 0.0)
    ((:curvature __curvature) 0.0)
    ((:steer_angle __steer_angle) 0.0)
    ((:steer_angle_feedforward __steer_angle_feedforward) 0.0)
    ((:steer_angle_lateral_contribution __steer_angle_lateral_contribution) 0.0)
    ((:steer_angle_lateral_rate_contribution __steer_angle_lateral_rate_contribution) 0.0)
    ((:steer_angle_heading_contribution __steer_angle_heading_contribution) 0.0)
    ((:steer_angle_heading_rate_contribution __steer_angle_heading_rate_contribution) 0.0)
    ((:steer_angle_feedback __steer_angle_feedback) 0.0)
    ((:steering_position __steering_position) 0.0)
    ((:ref_speed __ref_speed) 0.0)
    ((:steer_angle_limited __steer_angle_limited) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _lateral_error (float __lateral_error))
   (setq _ref_heading (float __ref_heading))
   (setq _heading (float __heading))
   (setq _heading_error (float __heading_error))
   (setq _heading_error_rate (float __heading_error_rate))
   (setq _lateral_error_rate (float __lateral_error_rate))
   (setq _curvature (float __curvature))
   (setq _steer_angle (float __steer_angle))
   (setq _steer_angle_feedforward (float __steer_angle_feedforward))
   (setq _steer_angle_lateral_contribution (float __steer_angle_lateral_contribution))
   (setq _steer_angle_lateral_rate_contribution (float __steer_angle_lateral_rate_contribution))
   (setq _steer_angle_heading_contribution (float __steer_angle_heading_contribution))
   (setq _steer_angle_heading_rate_contribution (float __steer_angle_heading_rate_contribution))
   (setq _steer_angle_feedback (float __steer_angle_feedback))
   (setq _steering_position (float __steering_position))
   (setq _ref_speed (float __ref_speed))
   (setq _steer_angle_limited (float __steer_angle_limited))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lateral_error
   (&optional __lateral_error)
   (if __lateral_error (setq _lateral_error __lateral_error)) _lateral_error)
  (:ref_heading
   (&optional __ref_heading)
   (if __ref_heading (setq _ref_heading __ref_heading)) _ref_heading)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:heading_error
   (&optional __heading_error)
   (if __heading_error (setq _heading_error __heading_error)) _heading_error)
  (:heading_error_rate
   (&optional __heading_error_rate)
   (if __heading_error_rate (setq _heading_error_rate __heading_error_rate)) _heading_error_rate)
  (:lateral_error_rate
   (&optional __lateral_error_rate)
   (if __lateral_error_rate (setq _lateral_error_rate __lateral_error_rate)) _lateral_error_rate)
  (:curvature
   (&optional __curvature)
   (if __curvature (setq _curvature __curvature)) _curvature)
  (:steer_angle
   (&optional __steer_angle)
   (if __steer_angle (setq _steer_angle __steer_angle)) _steer_angle)
  (:steer_angle_feedforward
   (&optional __steer_angle_feedforward)
   (if __steer_angle_feedforward (setq _steer_angle_feedforward __steer_angle_feedforward)) _steer_angle_feedforward)
  (:steer_angle_lateral_contribution
   (&optional __steer_angle_lateral_contribution)
   (if __steer_angle_lateral_contribution (setq _steer_angle_lateral_contribution __steer_angle_lateral_contribution)) _steer_angle_lateral_contribution)
  (:steer_angle_lateral_rate_contribution
   (&optional __steer_angle_lateral_rate_contribution)
   (if __steer_angle_lateral_rate_contribution (setq _steer_angle_lateral_rate_contribution __steer_angle_lateral_rate_contribution)) _steer_angle_lateral_rate_contribution)
  (:steer_angle_heading_contribution
   (&optional __steer_angle_heading_contribution)
   (if __steer_angle_heading_contribution (setq _steer_angle_heading_contribution __steer_angle_heading_contribution)) _steer_angle_heading_contribution)
  (:steer_angle_heading_rate_contribution
   (&optional __steer_angle_heading_rate_contribution)
   (if __steer_angle_heading_rate_contribution (setq _steer_angle_heading_rate_contribution __steer_angle_heading_rate_contribution)) _steer_angle_heading_rate_contribution)
  (:steer_angle_feedback
   (&optional __steer_angle_feedback)
   (if __steer_angle_feedback (setq _steer_angle_feedback __steer_angle_feedback)) _steer_angle_feedback)
  (:steering_position
   (&optional __steering_position)
   (if __steering_position (setq _steering_position __steering_position)) _steering_position)
  (:ref_speed
   (&optional __ref_speed)
   (if __ref_speed (setq _ref_speed __ref_speed)) _ref_speed)
  (:steer_angle_limited
   (&optional __steer_angle_limited)
   (if __steer_angle_limited (setq _steer_angle_limited __steer_angle_limited)) _steer_angle_limited)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _lateral_error
    8
    ;; float64 _ref_heading
    8
    ;; float64 _heading
    8
    ;; float64 _heading_error
    8
    ;; float64 _heading_error_rate
    8
    ;; float64 _lateral_error_rate
    8
    ;; float64 _curvature
    8
    ;; float64 _steer_angle
    8
    ;; float64 _steer_angle_feedforward
    8
    ;; float64 _steer_angle_lateral_contribution
    8
    ;; float64 _steer_angle_lateral_rate_contribution
    8
    ;; float64 _steer_angle_heading_contribution
    8
    ;; float64 _steer_angle_heading_rate_contribution
    8
    ;; float64 _steer_angle_feedback
    8
    ;; float64 _steering_position
    8
    ;; float64 _ref_speed
    8
    ;; float64 _steer_angle_limited
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _lateral_error
       (sys::poke _lateral_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ref_heading
       (sys::poke _ref_heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading_error
       (sys::poke _heading_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading_error_rate
       (sys::poke _heading_error_rate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lateral_error_rate
       (sys::poke _lateral_error_rate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _curvature
       (sys::poke _curvature (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle
       (sys::poke _steer_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_feedforward
       (sys::poke _steer_angle_feedforward (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_lateral_contribution
       (sys::poke _steer_angle_lateral_contribution (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_lateral_rate_contribution
       (sys::poke _steer_angle_lateral_rate_contribution (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_heading_contribution
       (sys::poke _steer_angle_heading_contribution (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_heading_rate_contribution
       (sys::poke _steer_angle_heading_rate_contribution (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_feedback
       (sys::poke _steer_angle_feedback (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_position
       (sys::poke _steering_position (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ref_speed
       (sys::poke _ref_speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_angle_limited
       (sys::poke _steer_angle_limited (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _lateral_error
     (setq _lateral_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ref_heading
     (setq _ref_heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading
     (setq _heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading_error
     (setq _heading_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading_error_rate
     (setq _heading_error_rate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lateral_error_rate
     (setq _lateral_error_rate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _curvature
     (setq _curvature (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle
     (setq _steer_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_feedforward
     (setq _steer_angle_feedforward (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_lateral_contribution
     (setq _steer_angle_lateral_contribution (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_lateral_rate_contribution
     (setq _steer_angle_lateral_rate_contribution (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_heading_contribution
     (setq _steer_angle_heading_contribution (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_heading_rate_contribution
     (setq _steer_angle_heading_rate_contribution (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_feedback
     (setq _steer_angle_feedback (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_position
     (setq _steering_position (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ref_speed
     (setq _ref_speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_angle_limited
     (setq _steer_angle_limited (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get car_msgs::lat_debug :md5sum-) "8df804ed8187912c1b683d311df460c6")
(setf (get car_msgs::lat_debug :datatype-) "car_msgs/lat_debug")
(setf (get car_msgs::lat_debug :definition-)
      "Header header

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



(provide :car_msgs/lat_debug "8df804ed8187912c1b683d311df460c6")


