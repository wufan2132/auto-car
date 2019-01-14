#include "ros/ros.h"
#include "car_msgs/localization.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/base_obstacle_list.h"
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point.h>
#include <Eigen/Dense>

//localization
ros::Publisher localization_markerPub;
visualization_msgs::Marker localization_marker_list;
double time_old = 0;
#define LONCALIZATION_PATH_LENGTH 300
//refrenceline
ros::Publisher refrenceline_markerPub;
visualization_msgs::Marker refrenceline_marker_list;
//trajectory
ros::Publisher trajectory_markerPub;
visualization_msgs::Marker trajectory_marker_list;
car_msgs::trajectory trajectory_msg_list;
//obstacles
ros::Publisher obstacles_markerPub;
visualization_msgs::Marker obstacles_marker_list;
car_msgs::base_obstacle_list obstacles_msg_list;
//samples
ros::Publisher samplers_markerPub;
visualization_msgs::Marker samplers_marker_list;
car_msgs::trajectory samplers_msg_list;
void localization_topic_callback(const car_msgs::localization::ConstPtr &localization_msg){
    double time_now = ros::Time::now().toSec();

    if(time_now - time_old > 0.01){
        time_old = time_now;
        //显示已走轨迹
        localization_marker_list.header.frame_id = "map";
        localization_marker_list.header.stamp = ros::Time::now();
        localization_marker_list.ns = "my_namespace";
        localization_marker_list.id = 2;
        localization_marker_list.type = visualization_msgs::Marker::SPHERE_LIST;
        localization_marker_list.action = visualization_msgs::Marker::ADD;

        localization_marker_list.scale.x = 0.1;
        localization_marker_list.scale.y = 0.1;
        localization_marker_list.scale.z = 0.1;
        localization_marker_list.color.a = 1.0; // Don't forget to set the alpha!
        localization_marker_list.color.r = 0.0;
        localization_marker_list.color.g = 1.0;
        localization_marker_list.color.b = 0.0;

        if(localization_marker_list.points.size() > LONCALIZATION_PATH_LENGTH)
            localization_marker_list.points.erase(localization_marker_list.points.begin());
        localization_marker_list.points.push_back(localization_msg->position);

        localization_markerPub.publish(localization_marker_list);

        //显示路径
        if(refrenceline_marker_list.points.size() > 0){
            refrenceline_marker_list.header.frame_id = "map";
            refrenceline_marker_list.header.stamp = ros::Time::now();
            refrenceline_marker_list.ns = "my_namespace";
            refrenceline_marker_list.id = 3;
            refrenceline_marker_list.type = visualization_msgs::Marker::SPHERE_LIST;
            refrenceline_marker_list.action = visualization_msgs::Marker::ADD;

            refrenceline_marker_list.scale.x = 0.1;
            refrenceline_marker_list.scale.y = 0.1;
            refrenceline_marker_list.scale.z = 0.1;
            refrenceline_marker_list.color.a = 0.7; // Don't forget to set the alpha!
            refrenceline_marker_list.color.r = 1.0;
            refrenceline_marker_list.color.g = 0.0;
            refrenceline_marker_list.color.b = 0.0;
            refrenceline_markerPub.publish(refrenceline_marker_list);
        }
        //显示目标轨迹
        if(trajectory_msg_list.total_path_length > 0){
            for(int i = 0;i < trajectory_msg_list.total_path_length;i++){
                trajectory_marker_list.header.frame_id = "map";
                trajectory_marker_list.header.stamp = ros::Time::now();
                trajectory_marker_list.ns = "my_namespace";
                trajectory_marker_list.id = i;
                trajectory_marker_list.type = visualization_msgs::Marker::ARROW;
                trajectory_marker_list.action = visualization_msgs::Marker::ADD;

                trajectory_marker_list.pose.position.x = trajectory_msg_list.trajectory_path[i].x;
                trajectory_marker_list.pose.position.y = trajectory_msg_list.trajectory_path[i].y;
                trajectory_marker_list.pose.position.z = trajectory_msg_list.trajectory_path[i].z;


                Eigen::Matrix3d R;
                R = Eigen::AngleAxisd(trajectory_msg_list.trajectory_path[i].theta, Eigen::Vector3d::UnitZ())
                    * Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY())
                    * Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX());
                //RotationMatrix to Quaterniond
                Eigen::Quaterniond q; 
                q = R;    

                trajectory_marker_list.pose.orientation.x = q.x();
                trajectory_marker_list.pose.orientation.y = q.y();
                trajectory_marker_list.pose.orientation.z = q.z();
                trajectory_marker_list.pose.orientation.w = q.w();

                trajectory_marker_list.scale.x = 0.3;
                trajectory_marker_list.scale.y = 0.08;
                trajectory_marker_list.scale.z = 0.08;
                trajectory_marker_list.color.a = 1.0; // Don't forget to set the alpha!
                trajectory_marker_list.color.r = 0.0;
                trajectory_marker_list.color.g = 1.0;
                trajectory_marker_list.color.b = 1.0;
                trajectory_markerPub.publish(trajectory_marker_list);
            }
        }
        //显示障碍
        if(obstacles_msg_list.list.size() > 0){
            for(int i = 0;i < obstacles_msg_list.list.size();i++){
                obstacles_marker_list.header.frame_id = "map";
                obstacles_marker_list.header.stamp = ros::Time::now();
                obstacles_marker_list.ns = "my_namespace";
                obstacles_marker_list.id = i;
                if(obstacles_msg_list.list[i].type == 0) //圆形
                    obstacles_marker_list.type = visualization_msgs::Marker::SPHERE;
                else if(obstacles_msg_list.list[i].type == 1) //方形 
                    obstacles_marker_list.type = visualization_msgs::Marker::CUBE;
                obstacles_marker_list.action = visualization_msgs::Marker::ADD;

                obstacles_marker_list.pose.position.x = obstacles_msg_list.list[i].xa[0];
                obstacles_marker_list.pose.position.y = obstacles_msg_list.list[i].ya[0];
                obstacles_marker_list.pose.position.z = (obstacles_msg_list.list[i].a + obstacles_msg_list.list[i].b)/4;


                Eigen::Matrix3d R;
                R = Eigen::AngleAxisd(obstacles_msg_list.list[i].theta_a[0], Eigen::Vector3d::UnitZ())
                    * Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY())
                    * Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX());
                //RotationMatrix to Quaterniond
                Eigen::Quaterniond q; 
                q = R;    

                obstacles_marker_list.pose.orientation.x = q.x();
                obstacles_marker_list.pose.orientation.y = q.y();
                obstacles_marker_list.pose.orientation.z = q.z();
                obstacles_marker_list.pose.orientation.w = q.w();

                obstacles_marker_list.scale.x = obstacles_msg_list.list[i].a;
                obstacles_marker_list.scale.y = obstacles_msg_list.list[i].b;
                obstacles_marker_list.scale.z = (obstacles_msg_list.list[i].a + obstacles_msg_list.list[i].b)/2;
                obstacles_marker_list.color.a = 1.0; // Don't forget to set the alpha!
                obstacles_marker_list.color.r = 1.0;
                obstacles_marker_list.color.g = 0.0;
                obstacles_marker_list.color.b = 1.0;
                obstacles_markerPub.publish(obstacles_marker_list);
            }
        }
        //显示采样点
        if(samplers_msg_list.trajectory_path.size() > 0){
            for(int i = 0;i < samplers_msg_list.total_path_length;i++){
                samplers_marker_list.header.frame_id = "map";
                samplers_marker_list.header.stamp = ros::Time::now();
                samplers_marker_list.ns = "my_namespace";
                samplers_marker_list.id = i;
                samplers_marker_list.type = visualization_msgs::Marker::ARROW;
                samplers_marker_list.action = visualization_msgs::Marker::ADD;

                samplers_marker_list.pose.position.x = samplers_msg_list.trajectory_path[i].x;
                samplers_marker_list.pose.position.y = samplers_msg_list.trajectory_path[i].y;
                samplers_marker_list.pose.position.z = samplers_msg_list.trajectory_path[i].z;

                samplers_marker_list.scale.x = 0.2;
                samplers_marker_list.scale.y = 0.2;
                samplers_marker_list.scale.z = 0.2;
                samplers_marker_list.color.a = 1.0; // Don't forget to set the alpha!
                samplers_marker_list.color.r = 0.8;
                samplers_marker_list.color.g = 0.0;
                samplers_marker_list.color.b = 0.8;
                samplers_markerPub.publish(samplers_marker_list);
            }
        }
    }
}

void refrenceline_topic_callback(const car_msgs::trajectory::ConstPtr &refrenceline_msg){
    if(refrenceline_marker_list.points.size() < refrenceline_msg->total_path_length ){
        for(int i = 0;i < refrenceline_msg->total_path_length;i++){
            geometry_msgs::Point point_temp;
            point_temp.x = refrenceline_msg->trajectory_path[i].x;
            point_temp.y = refrenceline_msg->trajectory_path[i].y;
            point_temp.z = refrenceline_msg->trajectory_path[i].z;
            refrenceline_marker_list.points.push_back(point_temp);
        }
    }
}

void trajectory_topic_callback(const car_msgs::trajectory::ConstPtr &trajectory_msg){
    trajectory_msg_list = (*trajectory_msg);
    
    // trajectory_marker_list.points.clear();
    // for(int i = 0;i < trajectory_msg->total_path_length;i++){
    //     geometry_msgs::Point point_temp;
    //     point_temp.x = trajectory_msg->trajectory_path[i].x;
    //     point_temp.y = trajectory_msg->trajectory_path[i].y;
    //     point_temp.z = trajectory_msg->trajectory_path[i].z;
    //     trajectory_marker_list.points.push_back(point_temp);
    // }
}

void obstacles_topic_callback(const car_msgs::base_obstacle_list::ConstPtr &obstacles_msg){
    obstacles_msg_list = (*obstacles_msg);
}

void samplers_topic_callback(const car_msgs::trajectory::ConstPtr &samples_msg){
    samplers_msg_list = (*samples_msg);
}


int main(int argc, char **argv){
    ros::init(argc, argv, "showline");
    ros::NodeHandle n;

    localization_markerPub = n.advertise<visualization_msgs::Marker>("localization_Marker", 1000);
    ros::Subscriber localization_publisher = n.subscribe("localization_topic", 1, localization_topic_callback);

    refrenceline_markerPub = n.advertise<visualization_msgs::Marker>("refrenceline_Marker", 1000);
    ros::Subscriber refrenceline_publisher = n.subscribe("refrenceline_topic", 1, refrenceline_topic_callback);
    
    trajectory_markerPub = n.advertise<visualization_msgs::Marker>("trajectory_Marker", 5000);
    ros::Subscriber trajectory_publisher = n.subscribe("trajectory_topic", 1, trajectory_topic_callback);

    obstacles_markerPub = n.advertise<visualization_msgs::Marker>("obstacles_Marker", 5000);
    ros::Subscriber obstacles_publisher = n.subscribe("obstacle_topic", 1, obstacles_topic_callback);

    samplers_markerPub = n.advertise<visualization_msgs::Marker>("samplers_Marker", 5000);
    ros::Subscriber samplers_publisher = n.subscribe("samplers_topic", 1, samplers_topic_callback);

    ros::spin();
    return 0;
}