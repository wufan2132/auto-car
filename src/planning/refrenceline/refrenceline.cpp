#include "planning/refrenceline.h"
#include "common/base/file_tool/file_tool.h"

using common::base::FileTool;

RefrencelineProvider::RefrencelineProvider(const YAML::Node& yaml_conf)
    : Task(yaml_conf) {
  conf_.start_point_x = yaml_conf["start_point_x"].as<double>();
  conf_.start_point_y = yaml_conf["start_point_y"].as<double>();
  conf_.end_point_x = yaml_conf["end_point_x"].as<double>();
  conf_.end_point_y = yaml_conf["end_point_y"].as<double>();

  conf_.origin_image_dir = yaml_conf["origin_image_dir"].as<string>();
  conf_.output_image_dir = yaml_conf["output_image_dir"].as<string>();
  conf_.origin_road_width = yaml_conf["origin_road_width"].as<int>();
  conf_.scale = yaml_conf["scale"].as<double>();

  conf_.spacing = yaml_conf["spacing"].as<double>();
  conf_.smooth_order = yaml_conf["smooth_order"].as<int>();

  astar = new Astar(yaml_conf["Astar"]);

  string pgm_yaml_dir =
      Common::convert_to_debugpath(yaml_conf["pgm_yaml_dir"].as<string>());
  map_convert = new MapConvert(FileTool::LoadFile(pgm_yaml_dir));
}

void RefrencelineProvider::Run(car_msgs::trajectory &origin_Trajectory) {
  //原始图像
  Image origin_img;
  origin_img.Readpgm(conf_.origin_image_dir);
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

  origin_img.Write24BMP(conf_.output_image_dir + "roadout_origin.bmp");
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

  ROS_INFO("RefrencelineProvider::process: Astar begin......");
  // A* 初始化
  vector<vector<int>> &maze = img.data;
  astar->InitAstar(maze);
  astar->setBMP(&img);
  // A*算法找寻路径
  list<MapPoint *> path = astar->GetPath(start, end, false);
  if (path.size() == 0) {
    ROS_ERROR("RefrencelineProvider::process: can not find a available path!");
    return;
  }
  //显示
  astar->show_path(path, astar->img);
  img.Write24BMP(conf_.output_image_dir + "roadout_pool.bmp");
  ROS_INFO("RefrencelineProvider::process: Astar finished!");
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
  ROS_INFO("RefrencelineProvider::process: path.size:%d",
           (int)path_origin.size());
  origin_img.Write24BMP(conf_.output_image_dir + "roadout_smooth.bmp");

  //生成原始轨迹，转化到pos坐标系
  origin_Trajectory.header.seq = 1;
  origin_Trajectory.trajectory_path.clear();
  auto it = path_origin.begin();
  for (int i = 0; it != path_origin.end(); i++, it++) {
    origin_Trajectory.trajectory_path.push_back(map_convert->MapToPos(**it));
  }
  origin_Trajectory.total_path_length =
      origin_Trajectory.trajectory_path.size();

  /**************************在原图上进行插值*********************************/
  // VectorXf point_x(path_origin.size()), point_y(path_origin.size());
  // auto it = path_origin.begin();
  // for (int i = 0; it != path_origin.end(); i++, it++){
  // 	point_x(i) = (*it)->x;
  // 	point_y(i) = (*it)->y;
  // }
  // Spline_Out csp;
  // Interpolating::Spline2D(point_x, point_y, csp ,conf_.spacing);
  // int len = csp.x.rows();
  // list<MapPoint *> path_finally;
  // for (int i = 0; i < len; i++){
  // 	int x = csp.x(i);
  // 	int y = csp.y(i);
  // 	path_finally.push_back(new MapPoint(x, y));
  // }
  // astar->show_path(path_finally, &origin_img, 'g');
  // ROS_INFO("RefrencelineProvider::process: path.size:%d",
  // (int)path_finally.size());
  // origin_img.Write24BMP(conf_.output_image_dir+"road_Interpolating.bmp");
}
