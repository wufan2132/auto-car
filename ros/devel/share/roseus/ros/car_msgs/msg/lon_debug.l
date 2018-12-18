;; Auto-generated. Do not edit!


(when (boundp 'car_msgs::lon_debug)
  (if (not (find-package "CAR_MSGS"))
    (make-package "CAR_MSGS"))
  (shadow 'lon_debug (find-package "CAR_MSGS")))
(unless (find-package "CAR_MSGS::LON_DEBUG")
  (make-package "CAR_MSGS::LON_DEBUG"))

(in-package "ROS")
;;//! \htmlinclude lon_debug.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass car_msgs::lon_debug
  :super ros::object
  :slots (_header _station_reference _station_error _station_error_limited _preview_station_error _station_out _speed_reference _speed_error _speed_controller_input_limited _preview_speed_reference _preview_speed_error _speed_out _preview_acceleration_reference _acceleration_cmd_closeloop _acceleration_cmd _acceleration_lookup _speed_lookup _calibration_value _throttle_cmd _brake_cmd _is_full_stop _slope_offset_compensation _current_station _path_remain ))

(defmethod car_msgs::lon_debug
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:station_reference __station_reference) 0.0)
    ((:station_error __station_error) 0.0)
    ((:station_error_limited __station_error_limited) 0.0)
    ((:preview_station_error __preview_station_error) 0.0)
    ((:station_out __station_out) 0.0)
    ((:speed_reference __speed_reference) 0.0)
    ((:speed_error __speed_error) 0.0)
    ((:speed_controller_input_limited __speed_controller_input_limited) 0.0)
    ((:preview_speed_reference __preview_speed_reference) 0.0)
    ((:preview_speed_error __preview_speed_error) 0.0)
    ((:speed_out __speed_out) 0.0)
    ((:preview_acceleration_reference __preview_acceleration_reference) 0.0)
    ((:acceleration_cmd_closeloop __acceleration_cmd_closeloop) 0.0)
    ((:acceleration_cmd __acceleration_cmd) 0.0)
    ((:acceleration_lookup __acceleration_lookup) 0.0)
    ((:speed_lookup __speed_lookup) 0.0)
    ((:calibration_value __calibration_value) 0.0)
    ((:throttle_cmd __throttle_cmd) 0.0)
    ((:brake_cmd __brake_cmd) 0.0)
    ((:is_full_stop __is_full_stop) nil)
    ((:slope_offset_compensation __slope_offset_compensation) 0.0)
    ((:current_station __current_station) 0.0)
    ((:path_remain __path_remain) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _station_reference (float __station_reference))
   (setq _station_error (float __station_error))
   (setq _station_error_limited (float __station_error_limited))
   (setq _preview_station_error (float __preview_station_error))
   (setq _station_out (float __station_out))
   (setq _speed_reference (float __speed_reference))
   (setq _speed_error (float __speed_error))
   (setq _speed_controller_input_limited (float __speed_controller_input_limited))
   (setq _preview_speed_reference (float __preview_speed_reference))
   (setq _preview_speed_error (float __preview_speed_error))
   (setq _speed_out (float __speed_out))
   (setq _preview_acceleration_reference (float __preview_acceleration_reference))
   (setq _acceleration_cmd_closeloop (float __acceleration_cmd_closeloop))
   (setq _acceleration_cmd (float __acceleration_cmd))
   (setq _acceleration_lookup (float __acceleration_lookup))
   (setq _speed_lookup (float __speed_lookup))
   (setq _calibration_value (float __calibration_value))
   (setq _throttle_cmd (float __throttle_cmd))
   (setq _brake_cmd (float __brake_cmd))
   (setq _is_full_stop __is_full_stop)
   (setq _slope_offset_compensation (float __slope_offset_compensation))
   (setq _current_station (float __current_station))
   (setq _path_remain (float __path_remain))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:station_reference
   (&optional __station_reference)
   (if __station_reference (setq _station_reference __station_reference)) _station_reference)
  (:station_error
   (&optional __station_error)
   (if __station_error (setq _station_error __station_error)) _station_error)
  (:station_error_limited
   (&optional __station_error_limited)
   (if __station_error_limited (setq _station_error_limited __station_error_limited)) _station_error_limited)
  (:preview_station_error
   (&optional __preview_station_error)
   (if __preview_station_error (setq _preview_station_error __preview_station_error)) _preview_station_error)
  (:station_out
   (&optional __station_out)
   (if __station_out (setq _station_out __station_out)) _station_out)
  (:speed_reference
   (&optional __speed_reference)
   (if __speed_reference (setq _speed_reference __speed_reference)) _speed_reference)
  (:speed_error
   (&optional __speed_error)
   (if __speed_error (setq _speed_error __speed_error)) _speed_error)
  (:speed_controller_input_limited
   (&optional __speed_controller_input_limited)
   (if __speed_controller_input_limited (setq _speed_controller_input_limited __speed_controller_input_limited)) _speed_controller_input_limited)
  (:preview_speed_reference
   (&optional __preview_speed_reference)
   (if __preview_speed_reference (setq _preview_speed_reference __preview_speed_reference)) _preview_speed_reference)
  (:preview_speed_error
   (&optional __preview_speed_error)
   (if __preview_speed_error (setq _preview_speed_error __preview_speed_error)) _preview_speed_error)
  (:speed_out
   (&optional __speed_out)
   (if __speed_out (setq _speed_out __speed_out)) _speed_out)
  (:preview_acceleration_reference
   (&optional __preview_acceleration_reference)
   (if __preview_acceleration_reference (setq _preview_acceleration_reference __preview_acceleration_reference)) _preview_acceleration_reference)
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
  (:throttle_cmd
   (&optional __throttle_cmd)
   (if __throttle_cmd (setq _throttle_cmd __throttle_cmd)) _throttle_cmd)
  (:brake_cmd
   (&optional __brake_cmd)
   (if __brake_cmd (setq _brake_cmd __brake_cmd)) _brake_cmd)
  (:is_full_stop
   (&optional __is_full_stop)
   (if __is_full_stop (setq _is_full_stop __is_full_stop)) _is_full_stop)
  (:slope_offset_compensation
   (&optional __slope_offset_compensation)
   (if __slope_offset_compensation (setq _slope_offset_compensation __slope_offset_compensation)) _slope_offset_compensation)
  (:current_station
   (&optional __current_station)
   (if __current_station (setq _current_station __current_station)) _current_station)
  (:path_remain
   (&optional __path_remain)
   (if __path_remain (setq _path_remain __path_remain)) _path_remain)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _station_reference
    8
    ;; float64 _station_error
    8
    ;; float64 _station_error_limited
    8
    ;; float64 _preview_station_error
    8
    ;; float64 _station_out
    8
    ;; float64 _speed_reference
    8
    ;; float64 _speed_error
    8
    ;; float64 _speed_controller_input_limited
    8
    ;; float64 _preview_speed_reference
    8
    ;; float64 _preview_speed_error
    8
    ;; float64 _speed_out
    8
    ;; float64 _preview_acceleration_reference
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
    ;; float64 _throttle_cmd
    8
    ;; float64 _brake_cmd
    8
    ;; bool _is_full_stop
    1
    ;; float64 _slope_offset_compensation
    8
    ;; float64 _current_station
    8
    ;; float64 _path_remain
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _station_reference
       (sys::poke _station_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _station_error
       (sys::poke _station_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _station_error_limited
       (sys::poke _station_error_limited (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _preview_station_error
       (sys::poke _preview_station_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _station_out
       (sys::poke _station_out (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_reference
       (sys::poke _speed_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_error
       (sys::poke _speed_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_controller_input_limited
       (sys::poke _speed_controller_input_limited (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _preview_speed_reference
       (sys::poke _preview_speed_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _preview_speed_error
       (sys::poke _preview_speed_error (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_out
       (sys::poke _speed_out (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _preview_acceleration_reference
       (sys::poke _preview_acceleration_reference (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
     ;; float64 _throttle_cmd
       (sys::poke _throttle_cmd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _brake_cmd
       (sys::poke _brake_cmd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _is_full_stop
       (if _is_full_stop (write-byte -1 s) (write-byte 0 s))
     ;; float64 _slope_offset_compensation
       (sys::poke _slope_offset_compensation (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _current_station
       (sys::poke _current_station (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _path_remain
       (sys::poke _path_remain (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _station_reference
     (setq _station_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _station_error
     (setq _station_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _station_error_limited
     (setq _station_error_limited (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _preview_station_error
     (setq _preview_station_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _station_out
     (setq _station_out (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_reference
     (setq _speed_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_error
     (setq _speed_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_controller_input_limited
     (setq _speed_controller_input_limited (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _preview_speed_reference
     (setq _preview_speed_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _preview_speed_error
     (setq _preview_speed_error (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_out
     (setq _speed_out (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _preview_acceleration_reference
     (setq _preview_acceleration_reference (sys::peek buf ptr- :double)) (incf ptr- 8)
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
   ;; float64 _throttle_cmd
     (setq _throttle_cmd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _brake_cmd
     (setq _brake_cmd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _is_full_stop
     (setq _is_full_stop (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float64 _slope_offset_compensation
     (setq _slope_offset_compensation (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _current_station
     (setq _current_station (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _path_remain
     (setq _path_remain (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get car_msgs::lon_debug :md5sum-) "323d2f9871df4f44858dc872121f8cf2")
(setf (get car_msgs::lon_debug :datatype-) "car_msgs/lon_debug")
(setf (get car_msgs::lon_debug :definition-)
      "Header header

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



(provide :car_msgs/lon_debug "323d2f9871df4f44858dc872121f8cf2")


