;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::mpc_debug)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'mpc_debug (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::MPC_DEBUG")
  (make-package "CAR_MSGS::MPC_DEBUG"))

(in-package "ROS")
;;//! \htmlinclude mpc_debug.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::mpc_debug
  :super ros::object
  :slots (_header _lateral_error _ref_heading _heading _heading_error _heading_error_rate _lateral_error_rate _curvature _steer_angle _steer_angle_feedforward _steer_angle_lateral_contribution _steer_angle_lateral_rate_contribution _steer_angle_heading_contribution _steer_angle_heading_rate_contribution _steer_angle_feedback _steering_position _ref_speed _steer_angle_limited _station_reference _station_error _speed_reference _speed_error _acceleration_reference _is_full_stop _station_feedback _speed_feedback _acceleration_cmd_closeloop _acceleration_cmd _acceleration_lookup _speed_lookup _calibration_value _matrix_q_updated1 _matrix_q_updated2 _matrix_q_updated3 _matrix_q_updated4 _matrix_q_updated5 _matrix_q_updated6 _matrix_r_updated1 _matrix_r_updated2 ))

(defmethod car_msgs::mpc_debug
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
    ((:station_reference __station_reference) 0.0)
    ((:station_error __station_error) 0.0)
    ((:speed_reference __speed_reference) 0.0)
    ((:speed_error __speed_error) 0.0)
    ((:acceleration_reference __acceleration_reference) 0.0)
    ((:is_full_stop __is_full_stop) nil)
    ((:station_feedback __station_feedback) 0.0)
    ((:speed_feedback __speed_feedback) 0.0)
    ((:acceleration_cmd_closeloop __acceleration_cmd_closeloop) 0.0)
    ((:acceleration_cmd __acceleration_cmd) 0.0)
    ((:acceleration_lookup __acceleration_lookup) 0.0)
    ((:speed_lookup __speed_lookup) 0.0)
    ((:calibration_value __calibration_value) 0.0)
    ((:matrix_q_updated1 __matrix_q_updated1) 0.0)
    ((:matrix_q_updated2 __matrix_q_updated2) 0.0)
    ((:matrix_q_updated3 __matrix_q_updated3) 0.0)
    ((:matrix_q_updated4 __matrix_q_updated4) 0.0)
    ((:matrix_q_updated5 __matrix_q_updated5) 0.0)
    ((:matrix_q_updated6 __matrix_q_updated6) 0.0)
    ((:matrix_r_updated1 __matrix_r_updated1) 0.0)
    ((:matrix_r_updated2 __matrix_r_updated2) 0.0)
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
   (setq _station_reference (float __station_reference))
   (setq _station_error (float __station_error))
   (setq _speed_reference (float __speed_reference))
   (setq _speed_error (float __speed_error))
   (setq _acceleration_reference (float __acceleration_reference))
   (setq _is_full_stop __is_full_stop)
   (setq _station_feedback (float __station_feedback))
   (setq _speed_feedback (float __speed_feedback))
   (setq _acceleration_cmd_closeloop (float __acceleration_cmd_closeloop))
   (setq _acceleration_cmd (float __acceleration_cmd))
   (setq _acceleration_lookup (float __acceleration_lookup))
   (setq _speed_lookup (float __speed_lookup))
   (setq _calibration_value (float __calibration_value))
   (setq _matrix_q_updated1 (float __matrix_q_updated1))
   (setq _matrix_q_updated2 (float __matrix_q_updated2))
   (setq _matrix_q_updated3 (float __matrix_q_updated3))
   (setq _matrix_q_updated4 (float __matrix_q_updated4))
   (setq _matrix_q_updated5 (float __matrix_q_updated5))
   (setq _matrix_q_updated6 (float __matrix_q_updated6))
   (setq _matrix_r_updated1 (float __matrix_r_updated1))
   (setq _matrix_r_updated2 (float __matrix_r_updated2))
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
  (:station_reference
   (&optional __station_reference)
   (if __station_reference (setq _station_reference __station_reference)) _station_reference)
  (:station_error
   (&optional __station_error)
   (if __station_error (setq _station_error __station_error)) _station_error)
  (:speed_reference
   (&optional __speed_reference)
   (if __speed_reference (setq _speed_reference __speed_reference)) _speed_reference)
  (:speed_error
   (&optional __speed_error)
   (if __speed_error (setq _speed_error __speed_error)) _speed_error)
  (:acceleration_reference
   (&optional __acceleration_reference)
   (if __acceleration_reference (setq _acceleration_reference __acceleration_reference)) _acceleration_reference)
  (:is_full_stop
   (&optional __is_full_stop)
   (if __is_full_stop (setq _is_full_stop __is_full_stop)) _is_full_stop)
  (:station_feedback
   (&optional __station_feedback)
   (if __station_feedback (setq _station_feedback __station_feedback)) _station_feedback)
  (:speed_feedback
   (&optional __speed_feedback)
   (if __speed_feedback (setq _speed_feedback __speed_feedback)) _speed_feedback)
  (:acceleration_cmd_closeloop
   (&optional __acceleration_cmd_closeloop)
   (if __acceleration_cmd_closeloop (setq _acceleration_cmd_closeloop __acceleration_cmd_closeloop)) _acceleration_cmd_closeloop)
  (:acceleration_cmd
   (&optional __acceleration_cmd)
   (if __acceleration_cmd (setq _acceleration_cmd __acceleration_cmd)) _acceleration_cmd)
  (:acceleration_lookup
   (&optional __acceleration_lookup)
   (if __acceleration_lookup (setq _acceleration_lookup __acceleration_lookup)) _acceleration_lookup)
  (:speed_lookup
   (&optional __speed_lookup)
   (if __speed_lookup (setq _speed_lookup __speed_lookup)) _speed_lookup)
  (:calibration_value
   (&optional __calibration_value)
   (if __calibration_value (setq _calibration_value __calibration_value)) _calibration_value)
  (:matrix_q_updated1
   (&optional __matrix_q_updated1)
   (if __matrix_q_updated1 (setq _matrix_q_updated1 __matrix_q_updated1)) _matrix_q_updated1)
  (:matrix_q_updated2
   (&optional __matrix_q_updated2)
   (if __matrix_q_updated2 (setq _matrix_q_updated2 __matrix_q_updated2)) _matrix_q_updated2)
  (:matrix_q_updated3
   (&optional __matrix_q_updated3)
   (if __matrix_q_updated3 (setq _matrix_q_updated3 __matrix_q_updated3)) _matrix_q_updated3)
  (:matrix_q_updated4
   (&optional __matrix_q_updated4)
   (if __matrix_q_updated4 (setq _matrix_q_updated4 __matrix_q_updated4)) _matrix_q_updated4)
  (:matrix_q_updated5
   (&optional __matrix_q_updated5)
   (if __matrix_q_updated5 (setq _matrix_q_updated5 __matrix_q_updated5)) _matrix_q_updated5)
  (:matrix_q_updated6
   (&optional __matrix_q_updated6)
   (if __matrix_q_updated6 (setq _matrix_q_updated6 __matrix_q_updated6)) _matrix_q_updated6)
  (:matrix_r_updated1
   (&optional __matrix_r_updated1)
   (if __matrix_r_updated1 (setq _matrix_r_updated1 __matrix_r_updated1)) _matrix_r_updated1)
  (:matrix_r_updated2
   (&optional __matrix_r_updated2)
   (if __matrix_r_updated2 (setq _matrix_r_updated2 __matrix_r_updated2)) _matrix_r_updated2)
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
    ;; float64 _station_reference
    8
    ;; float64 _station_error
    8
    ;; float64 _speed_reference
    8
    ;; float64 _speed_error
    8
    ;; float64 _acceleration_reference
    8
    ;; bool _is_full_stop
    1
    ;; float64 _station_feedback
    8
    ;; float64 _speed_feedback
    8
    ;; float64 _acceleration_cmd_closeloop
    8
    ;; float64 _acceleration_cmd
    8
    ;; float64 _acceleration_lookup
    8
    ;; float64 _speed_lookup
    8
    ;; float64 _calibration_value
    8
    ;; float64 _matrix_q_updated1
    8
    ;; float64 _matrix_q_updated2
    8
    ;; float64 _matrix_q_updated3
    8
    ;; float64 _matrix_q_updated4
    8
    ;; float64 _matrix_q_updated5
    8
    ;; float64 _matrix_q_updated6
    8
    ;; float64 _matrix_r_updated1
    8
    ;; float64 _matrix_r_updated2
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
     ;; float64 _station_reference
       (sys::poke _station_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _station_error
       (sys::poke _station_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_reference
       (sys::poke _speed_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_error
       (sys::poke _speed_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _acceleration_reference
       (sys::poke _acceleration_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _is_full_stop
       (if _is_full_stop (write-byte -1 s) (write-byte 0 s))
     ;; float64 _station_feedback
       (sys::poke _station_feedback (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_feedback
       (sys::poke _speed_feedback (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _acceleration_cmd_closeloop
       (sys::poke _acceleration_cmd_closeloop (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _acceleration_cmd
       (sys::poke _acceleration_cmd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _acceleration_lookup
       (sys::poke _acceleration_lookup (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_lookup
       (sys::poke _speed_lookup (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _calibration_value
       (sys::poke _calibration_value (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_q_updated1
       (sys::poke _matrix_q_updated1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_q_updated2
       (sys::poke _matrix_q_updated2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_q_updated3
       (sys::poke _matrix_q_updated3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_q_updated4
       (sys::poke _matrix_q_updated4 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_q_updated5
       (sys::poke _matrix_q_updated5 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_q_updated6
       (sys::poke _matrix_q_updated6 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_r_updated1
       (sys::poke _matrix_r_updated1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _matrix_r_updated2
       (sys::poke _matrix_r_updated2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
   ;; float64 _station_reference
     (setq _station_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _station_error
     (setq _station_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_reference
     (setq _speed_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_error
     (setq _speed_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _acceleration_reference
     (setq _acceleration_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _is_full_stop
     (setq _is_full_stop (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float64 _station_feedback
     (setq _station_feedback (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_feedback
     (setq _speed_feedback (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _acceleration_cmd_closeloop
     (setq _acceleration_cmd_closeloop (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _acceleration_cmd
     (setq _acceleration_cmd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _acceleration_lookup
     (setq _acceleration_lookup (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_lookup
     (setq _speed_lookup (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _calibration_value
     (setq _calibration_value (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_q_updated1
     (setq _matrix_q_updated1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_q_updated2
     (setq _matrix_q_updated2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_q_updated3
     (setq _matrix_q_updated3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_q_updated4
     (setq _matrix_q_updated4 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_q_updated5
     (setq _matrix_q_updated5 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_q_updated6
     (setq _matrix_q_updated6 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_r_updated1
     (setq _matrix_r_updated1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _matrix_r_updated2
     (setq _matrix_r_updated2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get car_msgs::mpc_debug :md5sum-) "8e149c22ce5f62150360f708ec54ee13")
(setf (get car_msgs::mpc_debug :datatype-) "car_msgs/mpc_debug")
(setf (get car_msgs::mpc_debug :definition-)
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



(provide :car_msgs/mpc_debug "8e149c22ce5f62150360f708ec54ee13")


