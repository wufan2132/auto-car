#include "usart.h"

namespace chassis {

using boost::asio::buffer;
using boost::asio::serial_port;

Usart::Usart(std::string port_name, uint32_t baud_rate) {
  serial_port_ = std::make_unique<serial_port>(ios_);
  CHECK(serial_port_) << "can not open serial port:" << port_name;
  uint32_t char_size = 8;
  serial_port_->open(port_name, err_code_);

  serial_port_->set_option(serial_port::baud_rate(baud_rate), err_code_);
  serial_port_->set_option(
      serial_port::flow_control(serial_port::flow_control::none), err_code_);
  serial_port_->set_option(serial_port::parity(serial_port::parity::none),
                           err_code_);
  serial_port_->set_option(serial_port::stop_bits(serial_port::stop_bits::one),
                           err_code_);
  serial_port_->set_option(serial_port::character_size(char_size), err_code_);
}

Usart::~Usart() {}

void Usart::send_to_serial(const uint16_t &throttle, const uint16_t &brake,
                           const int16_t &steer) {
  static int16_t cnt_test = 0;
  uint16_t Temp1 = 0;
  int16_t Temp2 = 0;
  uint8_t Cnt = 1;

  Send_BUF[Cnt++] = 0XAA;
  Send_BUF[Cnt++] = 0XAF;
  Send_BUF[Cnt++] = 0XA1;
  Send_BUF[Cnt++] = 0;

  Temp1 = throttle;
  Send_BUF[Cnt++] = BYTE1(Temp1);
  Send_BUF[Cnt++] = BYTE0(Temp1);

  Temp1 = brake;
  Send_BUF[Cnt++] = BYTE1(Temp1);
  Send_BUF[Cnt++] = BYTE0(Temp1);

  Temp2 = steer;
  Send_BUF[Cnt++] = BYTE1(Temp2);
  Send_BUF[Cnt++] = BYTE0(Temp2);

  Temp2 = cnt_test++;
  Send_BUF[Cnt++] = BYTE1(Temp2);
  Send_BUF[Cnt++] = BYTE0(Temp2);

  Send_BUF[4] = Cnt - 5;

  uint8_t Sum = 0;
  for (uint8_t i = 1; i < Cnt; i++) Sum += Send_BUF[i];
  Send_BUF[Cnt++] = Sum;
  Send_BUF[0] = Cnt - 1;

  write(*serial_port_, buffer(Send_BUF, Cnt));
}

void Usart::reveive_from_serial(double &speed, double &ang_x, double &ang_y,
                                double &ang_z, double &acc_x, double &acc_y,
                                double &acc_z, double &ang_v_x, double &ang_v_y,
                                double &ang_v_z, char &flag) {
#define RX_BUF_SIZE 64
  uint8_t Rx_buf[RX_BUF_SIZE];
  uint8_t Rx_buf_head[2];
  uint8_t i = 0;
  uint8_t Start = 0;
  uint8_t Length = 0;
  uint8_t Sum = 0;
  uint8_t Funtion = 0;

  // TODO: 阻塞问题
  while (1) {
    read(*serial_port_, buffer(&Rx_buf[0], 1));
    if (Rx_buf[0] == 0XAA) {
      read(*serial_port_, buffer(&Rx_buf[1], 1));
      if (Rx_buf[1] == 0XAA) {
        read(*serial_port_, buffer(&Rx_buf[2], 1));
        read(*serial_port_, buffer(&Rx_buf[3], 1));
        read(*serial_port_, buffer(&Rx_buf[4], Rx_buf[3] + 1));
        break;
      }
    }
  }

  Length = Rx_buf[i + 3] + 4;
  Start = i;
  Funtion = Rx_buf[i + 2];

  for (i = 0; i < Length; i++) Sum += Rx_buf[Start + i];

  if (Sum == Rx_buf[Start + Length]) {
    switch (Funtion) {
      case 0xA1:
        speed = *(float *)(&Rx_buf[Start + 4]);
        ang_x = *(float *)(&Rx_buf[Start + 8]);
        ang_y = *(float *)(&Rx_buf[Start + 12]);
        ang_z = *(float *)(&Rx_buf[Start + 16]);
        acc_x = *(float *)(&Rx_buf[Start + 20]);
        acc_y = *(float *)(&Rx_buf[Start + 24]);
        acc_z = *(float *)(&Rx_buf[Start + 28]);
        ang_v_x = *(float *)(&Rx_buf[Start + 32]);
        ang_v_y = *(float *)(&Rx_buf[Start + 36]);
        ang_v_z = *(float *)(&Rx_buf[Start + 40]);
        flag = *(char *)(&Rx_buf[Start + 44]);
        break;
      default:
        break;
    }
  }
}

}  // namespace chassis