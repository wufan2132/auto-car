
(cl:in-package :asdf)

(defsystem "car_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "chassis" :depends-on ("_package_chassis"))
    (:file "_package_chassis" :depends-on ("_package"))
    (:file "control_cmd" :depends-on ("_package_control_cmd"))
    (:file "_package_control_cmd" :depends-on ("_package"))
    (:file "debug" :depends-on ("_package_debug"))
    (:file "_package_debug" :depends-on ("_package"))
    (:file "lat_debug" :depends-on ("_package_lat_debug"))
    (:file "_package_lat_debug" :depends-on ("_package"))
    (:file "localization" :depends-on ("_package_localization"))
    (:file "_package_localization" :depends-on ("_package"))
    (:file "lon_debug" :depends-on ("_package_lon_debug"))
    (:file "_package_lon_debug" :depends-on ("_package"))
    (:file "mpc_debug" :depends-on ("_package_mpc_debug"))
    (:file "_package_mpc_debug" :depends-on ("_package"))
    (:file "trajectory" :depends-on ("_package_trajectory"))
    (:file "_package_trajectory" :depends-on ("_package"))
    (:file "trajectory_point" :depends-on ("_package_trajectory_point"))
    (:file "_package_trajectory_point" :depends-on ("_package"))
    (:file "vehicle_state" :depends-on ("_package_vehicle_state"))
    (:file "_package_vehicle_state" :depends-on ("_package"))
  ))