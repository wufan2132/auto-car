#ifndef CHASSIS_H
#define CHASSIS_H
#include "ros/ros.h"
#include "msgs/chassis.h"
#include "msgs/chassisCommand.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Chassis_class_{
  double x;
  double y;
  double yaw;
  double speed;
  double acc;
  double steer;
}Chassis_class;

typedef struct ChassisCommand_class_{
    double throttle;
    double brake;
    double steering;
}ChassisCommand_class;

typedef struct Socket_class_{
  int sock;
  struct sockaddr_in servaddr;
  char recvbuf[1024];
}Socket_class;

class CarChassis{
public:
    ~CarChassis(){
        close(chassis_socket_.sock);
        };

    void Init(void);
    void communicate(const msgs::chassisCommand &chassisCommand);
    void chassisCommand_topic_callback(const msgs::chassisCommand &chassisCommand);

    ros::NodeHandle car_chassis_NodeHandle;
    ros::Publisher chassis_publisher;

private:
    Socket_class chassis_socket_;
};

#endif