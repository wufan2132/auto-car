#include "ros/ros.h"
#include "car_msgs/localization.h"
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

ros::Publisher markerPub;
visualization_msgs::Marker marker_list;
double time_old = 0;

void localization_topic_callback(const car_msgs::localization::ConstPtr &localization_msg){
    double time_now = ros::Time::now().toSec();
    if(time_now - time_old > 0.01){
        time_old = time_now;

        marker_list.header.frame_id = "map";
        marker_list.header.stamp = ros::Time::now();
        marker_list.ns = "my_namespace";
        marker_list.id = 2;
        marker_list.type = visualization_msgs::Marker::SPHERE_LIST;
        marker_list.action = visualization_msgs::Marker::ADD;

        marker_list.scale.x = 0.2;
        marker_list.scale.y = 0.2;
        marker_list.scale.z = 0.2;
        marker_list.color.a = 1.0; // Don't forget to set the alpha!
        marker_list.color.r = 0.0;
        marker_list.color.g = 1.0;
        marker_list.color.b = 0.0;
        marker_list.points.push_back(localization_msg->position);

        markerPub.publish(marker_list);
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "showline");
    ros::NodeHandle n;

    markerPub = n.advertise<visualization_msgs::Marker>("Marker", 1000);
    ros::Subscriber localization_publisher = n.subscribe("localization_topic", 1, localization_topic_callback);

    ros::spin();
    return 0;
}