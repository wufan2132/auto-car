// #include"planning/config"


// user_config::user_config(YAML::Node planning_conf)
//     :planning_conf(),
//      interpolating_conf,
//      optimizer_conf  {}




// user_config::Car_Planning_Conf::Car_Planning_Conf(YAML::Node planning_conf)
// {
//     conf.mode = planning_conf["mode"].as<string>();
//     conf.period = planning_conf["period"].as<double>();
//     conf.wait_time = planning_conf["wait_time"].as<double>();
//     conf.trajectory_dir = planning_conf["trajectory_dir"].as<string>();
//     conf.sampling_period = planning_conf["sampling_period"].as<int>();
//     optimizer = new path_optimizer(planning_conf["path_optimizer_conf"]);
// }

// user_config::Interpolating_conf::Interpolating_conf(YAML::Node planning_conf)
// {
//     conf.mode = planning_conf["mode"].as<string>();
//     conf.period = planning_conf["period"].as<double>();
//     conf.wait_time = planning_conf["wait_time"].as<double>();
//     conf.trajectory_dir = planning_conf["trajectory_dir"].as<string>();
//     conf.sampling_period = planning_conf["sampling_period"].as<int>();
//     optimizer = new path_optimizer(planning_conf["path_optimizer_conf"]);
// }

// user_config::path_optimizer_Conf::path_optimizer_Conf(YAML::Node planning_conf)
// {
//     conf.mode = planning_conf["mode"].as<string>();
//     conf.period = planning_conf["period"].as<double>();
//     conf.wait_time = planning_conf["wait_time"].as<double>();
//     conf.trajectory_dir = planning_conf["trajectory_dir"].as<string>();
//     conf.sampling_period = planning_conf["sampling_period"].as<int>();
//     optimizer = new path_optimizer(planning_conf["path_optimizer_conf"]);
// }