#include "ros/ros.h"
#include "std_msgs/String.h"
#include "control/controller.h"
#include <time.h>
// void messageCallback(const std_msgs::String::ConstPtr& msg)//每次该节点收到一条消息时都调用此函数，就可以使用或处理数据。本例中，将收到道数据在命令窗口中输出来  
// {
//     ROS_INFO("I heard: [%s]", msg->data.c_str());//用于在命令行中输出数据  
// }

// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "example1_b");
//     ros::NodeHandle n;
//     /////创建一个订阅者，并从主题获取以message为名称的消息数据。设置缓冲区为1000个消息，处理消息句柄的回调函数>为messageCallback  
//     ros::Subscriber sub = n.subscribe("message", 1000, messageCallback);
//      //// ros::spin()库是节点读取数据道消息响应循环，当消息到达的时候，回调函数就会被调用。当按下Ctrl+C时，节点会退出消息循环，于是循环结束。  
//     ros::spin();
//     return 0;
// }
Controller controller;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "controller");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<msgs::chassisCommand>("chassisCommand", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    msgs::chassisCommand msg;
    
    msg.throttle = 55;
    msg.steering = 2;
    msg.brake = 3;

    msg.header.seq = rand();
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "foo";

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

// int main( int argc, char** argv )
// {
//   ros::init(argc, argv, "test_optim_node");
//   ros::NodeHandle n("~");
//   // 创建ros 定时器

// }
