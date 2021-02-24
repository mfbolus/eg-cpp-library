//===-- egcpp_h/linear_regression_model.h - Model Class ---------*- C++ -*-===//
//
// Copyright 2021 Michael Bolus
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file declares and partially defines an example linear regression model
/// class type.
///
/// \brief declares and partially defines an example class type
//===----------------------------------------------------------------------===//

#ifndef EGCPP_LINEAR_REGRESSION_MODEL_H
#define EGCPP_LINEAR_REGRESSION_MODEL_H

// TODO(mfbolus): this is a fudge. I believe the include should never actually
// be called, but it allows clangd to resolve these symbols.
#ifndef EGCPP
#include <egcpp>
#endif

/// An example namespace
namespace example {

/// \brief Linear Regression Model
class LinearRegressionModel {
 public:
  /**
   * Given input/output data, constructs and fits a new Linear Regression Model:
   *
   * y = C*x + d
   *
   * z ~ N(y, R)
   *
   * @brief      Constructs and fits a new LinearRegressionModel.
   *
   * @param      x     Input data [n_x x n_t]
   * @param      z     Measured output data [n_y x n_t]
   */
  LinearRegressionModel(const arma::mat& x, const arma::mat& z);

  /**
   * Constructs a new Linear Regression Model from parameters:
   *
   * y = C*x + d
   *
   * z ~ N(y, R)
   *
   * @brief      Constructs a new LinearRegressionModel
   *
   * @param      C     output matrix
   * @param      d     output bias
   * @param      R     measurement noise covariance
   */
  LinearRegressionModel(const arma::mat& C, const arma::vec& d,
                        const arma::mat& R);

  // ~LinearRegressionModel();

  /// get output matrix (C)
  auto C() const -> const arma::mat& { return C_; }

  /// get output bias (d)
  auto d() const -> const arma::vec& { return d_; }

  /// get measurement noise covariance (R)
  auto R() const -> const arma::vec& { return R_; }

  /**
   * @brief      simulates linear regression model
   *
   * @param      x          input data
   * @param      add_noise  whether to add measurement noise
   *
   * @return     model output
   */
  auto simulate(const arma::mat& x, bool add_noise = false) -> arma::mat;

  const size_t n_x;  ///< number of input channels
  const size_t n_y;  ///< number of output channels

 private:
  arma::mat C_;  ///< output matrix
  arma::vec d_;  ///< output bias
  arma::mat R_;  ///< measurement noise covariance
};
}  // namespace example

#endif
