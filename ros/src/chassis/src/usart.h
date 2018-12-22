#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define SEND_BUF_SIZE 64
using namespace std;
using namespace boost::asio;

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

typedef string anytype;

class Usart
{
 public:
     Usart(const anytype &port_name);
     ~Usart();
 
 private:
     bool init_port(const anytype port, const unsigned int char_size);
 
 public:
     void send_to_serial(const uint16_t &throttle,    //throttle
                         const uint16_t &brake,    //brake
                         const int16_t &steer);   //steer

    void reveive_from_serial(double &speed,
                                double &ang_x,
                                double &ang_y,
                                double &ang_z,
                                double &acc_x,
                                double &acc_y,
                                double &acc_z,
                                double &ang_v_x,
                                double &ang_v_y,
                                double &ang_v_z);
                                
    private:
        io_service m_ios;
        serial_port *pSerialPort;
        anytype m_port;
        boost::system::error_code m_ec;

        uint8_t Send_BUF[SEND_BUF_SIZE];
};
