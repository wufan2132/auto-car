/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <gflags/gflags.h>

DECLARE_string(base_dir);

DECLARE_string(system_run_mode);

DECLARE_string(car_name);

/**************************topic*************************/
//chassis
DECLARE_string(chassis_localization_topic);
DECLARE_string(chassis_car_state_topic);
//gazebo
DECLARE_string(gazebo_Odometry_topic);
DECLARE_string(gazebo_imu_topic);
DECLARE_string(planning_refrenceline_topic);
DECLARE_string(planning_trajectory_topic);
//control
DECLARE_string(control_controlcmd_topic);
DECLARE_string(control_debug_topic);
//other
DECLARE_string(param_topic);