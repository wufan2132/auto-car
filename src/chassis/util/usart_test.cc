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

TEST(uart_test, send) {
  Usart uart_adapter("/dev/ttyUSB0");
  LOG(INFO) << "usart init.....";
  while (1) {
    sleep(1);
    LOG(INFO) << "send .....";
    uart_adapter.send_to_serial(123, 123, 123);
    sleep(1);
    LOG(INFO) << "reveive .....";
    double data[11];
    char flag;
    uart_adapter.reveive_from_serial(data[0], data[1], data[2], data[3],
                                     data[4], data[5], data[6], data[7],
                                     data[8], data[9], flag);
    for (int i = 0; i < 10; i++) {
      LOG(INFO) << "data" << i << ":" << data[i];
    }
  }
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

}  // namespace chassis
