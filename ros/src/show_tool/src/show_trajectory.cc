#include "ros/ros.h"
#include "car_msgs/localization.h"
#include "car_msgs/trajectory.h"
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point.h>

ros::Publisher localization_markerPub;
visualization_msgs::Marker localization_marker_list;
double time_old = 0;

void localization_topic_callback(const car_msgs::localization::ConstPtr &localization_msg){
    double time_now = ros::Time::now().toSec();
    if(time_now - time_old > 0.01){
        time_old = time_now;

        localization_marker_list.header.frame_id = "map";
        localization_marker_list.header.stamp = ros::Time::now();
        localization_marker_list.ns = "my_namespace";
        localization_marker_list.id = 2;
        localization_marker_list.type = visualization_msgs::Marker::SPHERE_LIST;
        localization_marker_list.action = visualization_msgs::Marker::ADD;

        localization_marker_list.scale.x = 0.2;
        localization_marker_list.scale.y = 0.2;
        localization_marker_list.scale.z = 0.2;
        localization_marker_list.color.a = 1.0; // Don't forget to set the alpha!
        localization_marker_list.color.r = 0.0;
        localization_marker_list.color.g = 1.0;
        localization_marker_list.color.b = 0.0;


        localization_marker_list.points.push_back(localization_msg->position);

        localization_markerPub.publish(localization_marker_list);
    }
}

ros::Publisher path_markerPub;
visualization_msgs::Marker path_marker_list;
int flag = 0;
void path_topic_callback(const car_msgs::trajectory &trajectory_path){
    if(flag == 0){
        flag = 1;

        for(int i = 0;i < trajectory_path.total_path_length;i++){
            path_marker_list.header.frame_id = "map";
            path_marker_list.header.stamp = ros::Time::now();
            path_marker_list.ns = "my_namespace";
            path_marker_list.id = 3;
            path_marker_list.type = visualization_msgs::Marker::SPHERE_LIST;
            path_marker_list.action = visualization_msgs::Marker::ADD;

            path_marker_list.scale.x = 0.2;
            path_marker_list.scale.y = 0.2;
            path_marker_list.scale.z = 0.2;
            path_marker_list.color.a = 1.0; // Don't forget to set the alpha!
            path_marker_list.color.r = 1.0;
            path_marker_list.color.g = 0.0;
            path_marker_list.color.b = 0.0;
            geometry_msgs::Point point_temp;
            point_temp.x = trajectory_path.trajectory_path[i].x;
            point_temp.y = trajectory_path.trajectory_path[i].y;
            point_temp.z = trajectory_path.trajectory_path[i].z;
            path_marker_list.points.push_back(point_temp);
        }
        path_markerPub.publish(path_marker_list);
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "showline");
    ros::NodeHandle n;

    localization_markerPub = n.advertise<visualization_msgs::Marker>("localization_Marker", 1000);
    ros::Subscriber localization_publisher = n.subscribe("localization_topic", 1, localization_topic_callback);


    path_markerPub = n.advertise<visualization_msgs::Marker>("path_Marker", 1000);
    ros::Subscriber path_publisher = n.subscribe("planning_topic", 1, path_topic_callback);
    ros::spin();
    return 0;
}