#include "planning_gflags.h"

DEFINE_string(planning_conf_path, "/autocar/src/planning/planning_conf.yaml",
              "default planning conf data file");

DEFINE_string(record_trajectory_path,
              "/autocar/src/planning/file/trajectory/trajectory_test.csv",
              "default planning conf data file");

DEFINE_string(pgm_map_path,
              "/autocar/src/planning/file/map/trajectory_test.csv",
              "default planning conf data file");