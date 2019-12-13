/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/
#include "usart.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace chassis {

char SendBUF[64];
char ReadBUF[64];

TEST(uart_test, send) {
  Usart uart_adapter("/dev/ttyUSB0");
  for (int i = 0; i < 3; i++) {
    sleep(1);
    sprintf(SendBUF, "hello %d\n", i);
    LOG(INFO) << SendBUF;
    write(*uart_adapter.SerialPort(),
          boost::asio::buffer(SendBUF, strlen(SendBUF)));
  }
}

TEST(uart_test, read) {
  Usart uart_adapter("/dev/ttyUSB0");
  memset(ReadBUF, 0, sizeof(ReadBUF));
  for (int i = 0; i < 3; i++) {
    sleep(1);
    read(*uart_adapter.SerialPort(), boost::asio::buffer(ReadBUF, 10));
    LOG(INFO) << ReadBUF;
  }
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

}  // namespace chassis
