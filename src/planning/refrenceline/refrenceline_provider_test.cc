#include "refrenceline_provider.h"
#include <gtest/gtest.h>
#include <string>
#include "common/base/file_tool/conf_node.h"
#include "common/base/log.h"
#include "planning/common/planning_gflags.h"

namespace planning {

using common::base::ConfNode;

TEST(test, refrenceline_provider) {
  std::string yaml_str =
      "refrenceline_provider:\n\
    mode: csv\n\
    csv_path: /autocar/src/planning/file/trajectory/trajectory.csv\n\
    start_point_x: 0\n\
    start_point_y: 0\n\
    end_point_x: -6\n\
    end_point_y: 4\n\
    origin_image_conf_path: /autocar/src/planning/file/map/labmap.yaml\n\
    origin_image_path: /autocar/src/planning/file/map/labmap.pgm\n\
    output_image_path: /autocar/src/planning/file/output/\n\
    origin_road_width: 20\n\
    scale: 0.4\n\
    Astar:\n\
      kG: 2\n\
      kH: 1\n\
    spacing: 2\n\
    smooth_order: 5";
  Frame* frame = new Frame;
  RefrencelineProvider* p_RP = new RefrencelineProvider(YAML::Load(yaml_str));
  p_RP->Init();
  for (int i = 0; i < 10; i++) {
    if (p_RP->Run(frame))
      AINFO << "rp : ok";
    else {
      AINFO << "rp :  wait";
    }
    sleep(1);
  }
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

}  // namespace planning