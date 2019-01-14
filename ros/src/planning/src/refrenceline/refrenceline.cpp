#include "planning/refrenceline.h"


Refrenceline_provider::Refrenceline_provider(YAML::Node yaml_conf){
	conf.start_point_x = yaml_conf["start_point_x"].as<int>();
	conf.start_point_y = yaml_conf["start_point_y"].as<int>();
	conf.end_point_x = yaml_conf["end_point_x"].as<int>();
	conf.end_point_y = yaml_conf["end_point_y"].as<int>();

    conf.origin_image_dir = Common::convert_to_debugpath(yaml_conf["origin_image_dir"].as<string>());
    conf.output_image_dir = Common::convert_to_debugpath(yaml_conf["output_image_dir"].as<string>());
    conf.origin_road_width  = yaml_conf["origin_road_width"].as<int>();
    conf.scale = yaml_conf["scale"].as<double>();

	conf.spacing = yaml_conf["spacing"].as<double>();
	conf.smooth_order = yaml_conf["smooth_order"].as<int>();
	
	astar = new Astar(yaml_conf["Astar"]);

	string pgm_yaml_dir = Common::convert_to_debugpath(yaml_conf["pgm_yaml_dir"].as<string>());
	map_convert = new MapConvert(YAML::LoadFile(pgm_yaml_dir));
}

void Refrenceline_provider::process(car_msgs::trajectory& origin_Trajectory){
    //原始图像
    Image origin_img;
	origin_img.Readpgm(conf.origin_image_dir);
	//二值化
	origin_img.convert_twovalue();

	MapPoint origin_start(origin_img.convert_from_huatu(conf.start_point_x, conf.start_point_y));
	MapPoint origin_end(origin_img.convert_from_huatu(conf.end_point_x, conf.end_point_y));
		//标记起点与终点
	origin_img.drawPoint(origin_start.x, origin_start.y, 'g', 10);
	origin_img.drawPoint(origin_end.x, origin_end.y, 'g', 10);

	origin_img.Write24BMP(conf.output_image_dir+"roadout_origin.bmp");
	//压缩图像
	Image img;
	origin_img.compressionBMP(img, conf.scale);
	MapPoint start = img.point_scale(origin_start, conf.scale);
	MapPoint end = img.point_scale(origin_end, conf.scale);
	double road_width = conf.origin_road_width*conf.scale;
	double half_width = road_width / 2.0-1;

	road road_(img.data);
	road_.setBMP(&img);
	road_.Narrowing(half_width); //
	//标记起点与终点
	img.setcolor(start.x, start.y, 'g');
	img.setcolor(end.x, end.y, 'g');
	//map 映射
	start = road_.Map_to_road(start);
	end = road_.Map_to_road(end);
	//标记起点与终点
	img.setcolor(start.x, start.y, 'b');
	img.setcolor(end.x, end.y, 'b');


	//A* 初始化
	vector<vector<int>> &maze = img.data;
	astar->InitAstar(maze);
	astar->setBMP(&img); 
	//A*算法找寻路径 
	list<MapPoint *> path = astar->GetPath(start, end, false);
	//显示
	astar->show_path(path, astar->img);
	img.Write24BMP(conf.output_image_dir+"roadout_pool.bmp");

	//映射到原图
	list<MapPoint *> path_origin;
	for (auto it = path.begin(); it != path.end(); it++){
		MapPoint* p = new MapPoint(0,0);
		*p = img.point_rescale((**it), conf.scale);
		path_origin.push_back(p);
	}
	astar->smooth(path_origin,conf.smooth_order);
	//显示
	astar->show_path(path_origin, &origin_img, 'y');
	ROS_INFO("Refrenceline_provider::process: path.size:%d", (int)path_origin.size());
	origin_img.Write24BMP(conf.output_image_dir+"roadout_smooth.bmp");
	
	//生成原始轨迹，转化到pos坐标系
	origin_Trajectory.header.seq = 1; 
    origin_Trajectory.trajectory_path.clear();
	auto it = path_origin.begin();
	for (int i = 0; it != path_origin.end(); i++, it++){
		origin_Trajectory.trajectory_path.push_back(map_convert->MapToPos(**it));
	}
	origin_Trajectory.total_path_length = origin_Trajectory.trajectory_path.size();

	/**************************在原图上进行插值*********************************/
	// VectorXf point_x(path_origin.size()), point_y(path_origin.size());
	// auto it = path_origin.begin();
	// for (int i = 0; it != path_origin.end(); i++, it++){
	// 	point_x(i) = (*it)->x;
	// 	point_y(i) = (*it)->y;
	// }
	// Spline_Out csp;
	// Interpolating::Spline2D(point_x, point_y, csp ,conf.spacing);
	// int len = csp.x.rows();
	// list<MapPoint *> path_finally;
	// for (int i = 0; i < len; i++){
	// 	int x = csp.x(i);
	// 	int y = csp.y(i);
	// 	path_finally.push_back(new MapPoint(x, y));
	// }
	// astar->show_path(path_finally, &origin_img, 'g');
	// ROS_INFO("Refrenceline_provider::process: path.size:%d", (int)path_finally.size());
	// origin_img.Write24BMP(conf.output_image_dir+"road_Interpolating.bmp");
}
