#include "refrenceline_provider.h"
#include <string>
#include "common/base/file_tool/conf_node.h"
#include "planning/replay/replay.h"

namespace planning {

using common::base::ConfNode;
using common::base::ConfNode;

RefrencelineProvider::RefrencelineProvider(const common::base::ConfNode &yaml_conf)
    : Task(yaml_conf) {
  const auto &rp_conf = yaml_conf["refrenceline_provider"];
  conf_.mode = rp_conf["mode"].as<string>();
  //
  conf_.csv_path = rp_conf["csv_path"].as<string>();
  //
  conf_.start_point_x = rp_conf["start_point_x"].as<double>();
  conf_.start_point_y = rp_conf["start_point_y"].as<double>();
  conf_.end_point_x = rp_conf["end_point_x"].as<double>();
  conf_.end_point_y = rp_conf["end_point_y"].as<double>();

  conf_.origin_image_path = rp_conf["origin_image_path"].as<string>();
  conf_.output_image_path = rp_conf["output_image_path"].as<string>();
  conf_.origin_road_width = rp_conf["origin_road_width"].as<int>();
  conf_.scale = rp_conf["scale"].as<double>();
  conf_.spacing = rp_conf["spacing"].as<double>();
  conf_.smooth_order = rp_conf["smooth_order"].as<int>();
  astar = new Astar(rp_conf["Astar"]);

  std::string image_conf_path = rp_conf["origin_image_conf_path"].as<string>();
  AINFO << "image_conf_path: " << image_conf_path;
  AINFO << "origin_image_path: " << conf_.origin_image_path;
  map_convert = new MapConvert(ConfNode::LoadFile(image_conf_path));
}

RefrencelineProvider::~RefrencelineProvider() {}
bool RefrencelineProvider::Init() { is_ready_ = 0; }

bool RefrencelineProvider::Stop() { return true; }

bool RefrencelineProvider::Run(Frame *frame) {
  CHECK_NOTNULL(frame);
  // intput
  // output
  auto *raw_refrenceline = frame->mutable_raw_refrenceline();
  // process
  if (!work_thread_ && has_refrenceline_task_) {
    AINFO << "get refrenceline task";
    if (conf_.mode == "csv") {
      work_thread_ = std::make_unique<std::thread>(
          &RefrencelineProvider::GetRefrencelineFromCSV, this,
          raw_refrenceline);
    } else if (conf_.mode == "map") {
      work_thread_ = std::make_unique<std::thread>(
          &RefrencelineProvider::GetRefrencelineFromMap, this,
          raw_refrenceline);
    } else {
      AERROR << "unknow refrenceline source!";
    }
    has_refrenceline_task_ = 0;
  }
  // get result
  if (is_ready_ == 0) {
    return false;
  } else if (is_ready_ == 1) {
    if (work_thread_) {
      work_thread_->join();
      work_thread_.reset();
    }
    return true;
  } else {
    if (work_thread_) {
      work_thread_->join();
      work_thread_.reset();
    }
    return false;
  }
  return true;
}
void RefrencelineProvider::GetRefrencelineFromMap(
    car_msgs::trajectory *refrenceline) {
  CHECK_NOTNULL(refrenceline);
  //原始图像
  Image origin_img;
  origin_img.Readpgm(conf_.origin_image_path);
  //二值化
  origin_img.convert_twovalue();
  //初始化起点与终点
  // MapPoint origin_start(origin_img.convert_from_huatu(conf_.start_point_x,
  // conf_.start_point_y)); MapPoint
  // origin_end(origin_img.convert_from_huatu(conf_.end_point_x,
  // conf_.end_point_y));
  car_msgs::trajectory_point start_point, end_point;
  start_point.x = conf_.start_point_x;
  start_point.y = conf_.start_point_y;
  end_point.x = conf_.end_point_x;
  end_point.y = conf_.end_point_y;
  MapPoint origin_start = map_convert->PosToMap(start_point);
  MapPoint origin_end = map_convert->PosToMap(end_point);
  //标记起点与终点
  origin_img.drawPoint(origin_start.x, origin_start.y, 'r', 2);
  origin_img.drawPoint(origin_end.x, origin_end.y, 'g', 2);

  origin_img.Write24BMP(conf_.output_image_path + "roadout_origin.bmp");
  //压缩图像
  Image img;
  origin_img.compressionBMP(img, conf_.scale);
  MapPoint start = img.point_scale(origin_start, conf_.scale);
  MapPoint end = img.point_scale(origin_end, conf_.scale);
  double road_width = conf_.origin_road_width * conf_.scale;
  double half_width = road_width / 2.0 - 1;

  road road_(img.data);
  road_.setBMP(&img);
  road_.Narrowing(half_width);  //
  //标记起点与终点
  img.setcolor(start.x, start.y, 'g');
  img.setcolor(end.x, end.y, 'g');
  // map 映射
  start = road_.Map_to_road(start);
  end = road_.Map_to_road(end);
  //标记起点与终点
  img.setcolor(start.x, start.y, 'b');
  img.setcolor(end.x, end.y, 'b');

  AINFO << "RefrencelineProvider::process: Astar begin......";
  // A* 初始化
  vector<vector<int>> &maze = img.data;
  astar->InitAstar(maze);
  astar->setBMP(&img);
  // A*算法找寻路径
  list<MapPoint *> path = astar->GetPath(start, end, false);
  if (path.size() == 0) {
    AERROR << "RefrencelineProvider::process: can not find a available path!";
    is_ready_ = -1;
    return;
  }
  //显示
  astar->show_path(path, astar->img);
  img.Write24BMP(conf_.output_image_path + "roadout_pool.bmp");
  AINFO << "RefrencelineProvider::process: Astar finished!";
  //映射到原图
  list<MapPoint *> path_origin;
  for (auto it = path.begin(); it != path.end(); it++) {
    MapPoint *p = new MapPoint(0, 0);
    *p = img.point_rescale((**it), conf_.scale);
    path_origin.push_back(p);
  }
  astar->smooth(path_origin, conf_.smooth_order);
  //显示
  astar->show_path(path_origin, &origin_img, 'b');
  AINFO << "RefrencelineProvider::process: path.size:" << path_origin.size();
  origin_img.Write24BMP(conf_.output_image_path + "roadout_smooth.bmp");
  AINFO << "output images write to :" << conf_.output_image_path
        << "roadout_smooth.bmp";
  //生成原始轨迹，转化到pos坐标系
  refrenceline->header.seq = 1;
  refrenceline->trajectory_path.clear();
  auto it = path_origin.begin();
  for (int i = 0; it != path_origin.end(); i++, it++) {
    refrenceline->trajectory_path.push_back(map_convert->MapToPos(**it));
  }
  refrenceline->total_path_length = refrenceline->trajectory_path.size();
  // ok
  is_ready_ = 1;
}

void RefrencelineProvider::GetRefrencelineFromCSV(
    car_msgs::trajectory *refrenceline) {
  static int count = 0;
  Replay replayer(conf_.csv_path, "read");
  replayer.Reset();
  refrenceline->header.seq = count;
  refrenceline->trajectory_path.clear();
  car_msgs::trajectory_point point;
  while (replayer.ReadOnce(point)) {
    refrenceline->trajectory_path.push_back(point);
  }
  refrenceline->total_path_length = refrenceline->trajectory_path.size();
  AINFO << "GetRefrencelineFromCSV: " << refrenceline->total_path_length
        << " point.";
  count++;
  is_ready_ = 1;
}

}  // namespace planning