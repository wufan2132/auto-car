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
#include "active_set_qp_solver.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

namespace common {
namespace math {

using Eigen::MatrixXd;


TEST(ActiveSetQpSolver, simple_problem_01) {
  MatrixXd kernel_matrix(3, 3);
    kernel_matrix << 2 , 0 , 0 ,
                                      0 , 2 , 0 ,
                                       0 , 0 , 2;
  MatrixXd offset = MatrixXd::Zero(3, 1);

  MatrixXd affine_inequality_matrix;
  MatrixXd affine_inequality_boundary;
  MatrixXd affine_equality_matrix  = MatrixXd::Zero(1, 3);
  affine_equality_matrix  << 1 , 1 , 1;
  MatrixXd affine_equality_boundary = MatrixXd::Zero(1, 1);
  affine_equality_boundary  << 1;
  ActiveSetQpSolver solver(kernel_matrix, offset, affine_inequality_matrix,
                           affine_inequality_boundary, affine_equality_matrix,
                           affine_equality_boundary);
  solver.Solve();
  EXPECT_EQ(solver.params().rows() , 3);
  EXPECT_EQ(solver.params().cols() , 1);
  EXPECT_NEAR(solver.params()(0, 0), 0.33333333333, 1e-3);
  EXPECT_NEAR(solver.params()(1, 0), 0.33333333333, 1e-3);
  EXPECT_NEAR(solver.params()(2, 0), 0.33333333333, 1e-3);
}


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

}  // namespace math
}  // namespace common

