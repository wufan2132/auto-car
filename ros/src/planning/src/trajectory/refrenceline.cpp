#include "planning/refrenceline.h"


Refrenceline_provider::Refrenceline_provider(YAML::Node yaml_conf){
    conf.origin_image_dir = Common::convert_to_debugpath(yaml_conf["origin_image_dir"].as<string>());
    conf.output_image_dir = Common::convert_to_debugpath(yaml_conf["output_image_dir"].as<string>());
    conf.origin_road_width  = yaml_conf["origin_road_width"].as<int>();
    conf.scale = yaml_conf["scale"].as<double>();
}

void Refrenceline_provider::process(){
    //原始图像
    Image origin_img;
	origin_img.Read24BMP(conf.origin_image_dir);
	MapPoint origin_start(origin_img.convert_from_huatu(889, 102));
	MapPoint origin_end(origin_img.convert_from_huatu(133, 698));//(836, 430))
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
	Astar astar;
	vector<vector<int>> &maze = img.data;
	astar.InitAstar(maze);
	astar.setBMP(&img); 
	//A*算法找寻路径 
	list<MapPoint *> path = astar.GetPath(start, end, false);
	//显示
	astar.show_path(path, astar.img);
	img.Write24BMP(conf.output_image_dir+"roadout_pool.bmp");

	//映射到原图
	list<MapPoint *> path_origin;
	for (auto it = path.begin(); it != path.end(); it++){
		MapPoint* p = new MapPoint(0,0);
		*p = img.point_rescale((**it), conf.scale);
		path_origin.push_back(p);
	}
	astar.smooth(path_origin,6);
	//显示
	astar.show_path(path_origin, &origin_img, 'y');
	cout << "path.size:" << path_origin.size() << endl;
	origin_img.Write24BMP(conf.output_image_dir+"roadout.bmp");
	
	
	VectorXf point_x(path_origin.size()), point_y(path_origin.size());

	auto it = path_origin.begin();
	for (int i = 0; it != path_origin.end(); i++, it++){
		point_x(i) = (*it)->x;
		point_y(i) = (*it)->y;
	}

	Spline_Out csp;
	Interpolating::Spline2D(point_x, point_y, csp ,2);


	int len = csp.x.rows();
	list<MapPoint *> path_finally;
	for (int i = 0; i < len; i++){
		int x = csp.x(i);
		int y = csp.y(i);
		path_finally.push_back(new MapPoint(x, y));
	}

	astar.show_path(path_finally, &origin_img, 'g');
	cout << "path_output.size:" << path_finally.size() << endl;
	origin_img.Write24BMP(conf.output_image_dir+"road_Interpolating.bmp");
}
