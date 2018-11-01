// #include "chassis/car_chassis.h"
// #include "bitset"
// #define SERVERPORT 8887
// char* SERVERIP = "192.168.1.102";

// #define MYPORT 8884
// char* MYIP = "192.168.1.114";

// void CarChassis::Init(void){
//     if ((chassis_socket_.sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
//         ROS_INFO("socket"); 
//     memset(&chassis_socket_.servaddr, 0, sizeof(chassis_socket_.servaddr));
//     chassis_socket_.servaddr.sin_family = AF_INET;
//     chassis_socket_.servaddr.sin_port = htons(SERVERPORT);
//     chassis_socket_.servaddr.sin_addr.s_addr = inet_addr(SERVERIP);

    
//     memset(&chassis_socket_.localaddr, 0, sizeof(chassis_socket_.localaddr));
//     chassis_socket_.localaddr.sin_family = AF_INET;
//     chassis_socket_.localaddr.sin_port = htons(MYPORT);
//     chassis_socket_.localaddr.sin_addr.s_addr = INADDR_ANY;
//     bind(chassis_socket_.sock,(struct sockaddr*)&chassis_socket_.localaddr,sizeof chassis_socket_.localaddr);

//     chassis_publisher = car_chassis_NodeHandle.advertise<car_msgs::chassis>("chassis_topic", 1000);
// }

// void CarChassis::chassisCommand_topic_callback(const car_msgs::control &chassisCommand){
//     communicate(chassisCommand);
// }

// void CarChassis::communicate(const car_msgs::control &chassisCommand){
//     ChassisCommand_class ChassisCommand_temp;
//     Chassis_class chassis_temp;
//     car_msgs::chassis chassis_msg;

//     ChassisCommand_temp.throttle = chassisCommand.throttle;
//     ChassisCommand_temp.brake = chassisCommand.brake;
//     ChassisCommand_temp.steering = chassisCommand.steering;

//     sendto(chassis_socket_.sock, (char*)&ChassisCommand_temp, sizeof(ChassisCommand_temp), 0, (struct sockaddr *)&chassis_socket_.servaddr, sizeof(chassis_socket_.servaddr));
//     //int ret = recvfrom(chassis_socket_.sock, chassis_socket_.recvbuf, sizeof(chassis_socket_.recvbuf), 0, NULL, NULL);
//     socklen_t len = sizeof(chassis_socket_.localaddr);
//     int ret = recvfrom(chassis_socket_.sock, chassis_socket_.recvbuf, sizeof(chassis_socket_.recvbuf), 0,(struct sockaddr *)&chassis_socket_.localaddr, &len);
//     if (ret == -1){
//         if (errno == EINTR){
//             ROS_INFO("receive error"); 
//             return;
//         }
//     }
//     ROS_INFO("receive...");
//     chassis_temp = *(Chassis_class*)chassis_socket_.recvbuf;
//     chassis_msg.x = chassis_temp.x;
//     chassis_msg.y = chassis_temp.y;
//     chassis_msg.yaw = chassis_temp.yaw;
//     chassis_msg.speed = chassis_temp.speed;
//     chassis_msg.acc = 0;
//     chassis_msg.steer = chassis_temp.steer;
//     chassis_publisher.publish(chassis_msg);
//     memset(chassis_socket_.recvbuf, 0, sizeof(chassis_socket_.recvbuf));
// }