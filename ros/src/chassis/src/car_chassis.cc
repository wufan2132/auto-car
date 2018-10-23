#include "chassis/car_chassis.h"

#define MYPORT 8887
char* SERVERIP = "192.168.1.102";

void CarChassis::Init(void){
    if ((chassis_socket_.sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        ROS_INFO("socket"); 
    memset(&chassis_socket_.servaddr, 0, sizeof(chassis_socket_.servaddr));
    chassis_socket_.servaddr.sin_family = AF_INET;
    chassis_socket_.servaddr.sin_port = htons(MYPORT);
    chassis_socket_.servaddr.sin_addr.s_addr = inet_addr(SERVERIP);

    chassis_publisher = car_chassis_NodeHandle.advertise<msgs::chassis>("chassis_topic", 1000);
}

void CarChassis::chassisCommand_topic_callback(const msgs::chassisCommand &chassisCommand){
    communicate(chassisCommand);
}

void CarChassis::communicate(const msgs::chassisCommand &chassisCommand){
    ChassisCommand_class ChassisCommand_temp;
    Chassis_class chassis_temp;
    msgs::chassis chassis_msg;

    ChassisCommand_temp.throttle = chassisCommand.throttle;
    ChassisCommand_temp.brake = chassisCommand.brake;
    ChassisCommand_temp.steering = chassisCommand.steering;

    sendto(chassis_socket_.sock, (char*)&ChassisCommand_temp, sizeof(ChassisCommand_temp), 0, (struct sockaddr *)&chassis_socket_.servaddr, sizeof(chassis_socket_.servaddr));
    int ret = recvfrom(chassis_socket_.sock, chassis_socket_.recvbuf, sizeof(chassis_socket_.recvbuf), 0, NULL, NULL);
    if (ret == -1){
        if (errno == EINTR){
            ROS_INFO("receive error"); 
            return;
        }
    }
    ROS_INFO("receive...");
    chassis_temp = *(Chassis_class*)chassis_socket_.recvbuf;
    chassis_msg.x = chassis_temp.x;
    chassis_msg.y = chassis_temp.y;
    chassis_msg.yaw = chassis_temp.yaw;
    chassis_msg.speed = chassis_temp.speed;
    chassis_msg.acc = chassis_temp.acc;
    chassis_msg.steer = chassis_temp.steer;
    chassis_publisher.publish(chassis_msg);
    // memset(recvbuf, 0, sizeof(recvbuf));
}