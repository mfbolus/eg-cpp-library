//===-- egcpp_h/linear_model.h - Linear Model Class -------------*- C++ -*-===//
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
/// This file declares and partially defines an example linear model class type.
///
/// \brief declares and partially defines an example linear model class type
//===----------------------------------------------------------------------===//

#ifndef EGCPP_LINEAR_MODEL_H
#define EGCPP_LINEAR_MODEL_H

// this is just here so clangd can resolve these symbols.
#ifndef EGCPP
#include <egcpp>
#endif

/// An example namespace
namespace example {

/// \brief Linear Regression Model
class LinearModel {
 public:
  /**
   * Given input/output data, constructs and fits a new LinearModel:
   *
   * {{< katex display >}} \mathbf{y}_t = \mathbf{C} \mathbf{x}_{t} + \mathbf{d}
   * {{< /katex >}}
   *
   * {{< katex display >}} \mathbf{z}_t \sim \mathcal{N}\left(\mathbf{y}_t ,
   * \mathbf{R} \right) {{< /katex >}}
   *
   * where {{<katex>}} \mathbf{x}_{t} {{</katex>}}, {{<katex>}} \mathbf{y}_{t}
   * {{</katex>}}, and {{<katex>}} \mathbf{z}_{t} {{</katex>}} the input,
   * output, and measurement, respectively; {{<katex>}} \mathbf{C} {{</katex>}}
   * is the output matrix; {{<katex>}} \mathbf{d} {{</katex>}} is the output
   * bias; and {{<katex>}} \mathbf{R} {{</katex>}} is the covariance of the
   * assumed Gaussian measurement noise.
   *
   * @brief      Constructs and fits a new LinearModel.
   *
   * @param      x     Input data [n_x x n_t]
   * @param      z     Measured output data [n_y x n_t]
   */
  LinearModel(const arma::mat& x, const arma::mat& z);

  /**
   * Constructs a new LinearModel from parameters:
   *
   * {{< katex display >}} \mathbf{y}_t = \mathbf{C} \mathbf{x}_{t} + \mathbf{d}
   * {{< /katex >}}
   *
   * {{< katex display >}} \mathbf{z}_t \sim \mathcal{N}\left(\mathbf{y}_t ,
   * \mathbf{R} \right) {{< /katex >}}
   *
   * where {{<katex>}} \mathbf{x}_{t} {{</katex>}}, {{<katex>}} \mathbf{y}_{t}
   * {{</katex>}}, and {{<katex>}} \mathbf{z}_{t} {{</katex>}} the input,
   * output, and measurement, respectively; {{<katex>}} \mathbf{C} {{</katex>}}
   * is the output matrix; {{<katex>}} \mathbf{d} {{</katex>}} is the output
   * bias; and {{<katex>}} \mathbf{R} {{</katex>}} is the covariance of the
   * assumed Gaussian measurement noise.
   *
   * @brief      Constructs a new LinearModel
   *
   * @param      C     output matrix
   * @param      d     output bias
   * @param      R     measurement noise covariance
   */
  LinearModel(const arma::mat& C, const arma::vec& d,
                        const arma::mat& R);

  /// get output matrix (C)
  auto C() const -> const arma::mat& { return C_; }

  /// get output bias (d)
  auto d() const -> const arma::vec& { return d_; }

  /// get measurement noise covariance (R)
  auto R() const -> const arma::mat& { return R_; }

  /**
   * @brief      simulates linear model
   *
   * @param      x          input data
   * @param      add_noise  whether to add measurement noise
   *
   * @return     model output
   */
  auto simulate(const arma::mat& x, bool add_noise = false) -> arma::mat;

  const size_t n_x;  ///< number of input channels
  const size_t n_y;  ///< number of output channels

 protected:
  arma::mat C_;  ///< output matrix
  arma::vec d_;  ///< output bias

private:
  arma::mat R_;  ///< measurement noise covariance
};
}  // namespace example

#endif
