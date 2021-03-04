//===-- egcpp_h/poisson_model.h - Poisson Model Class -----------*- C++ -*-===//
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
/// This file declares and partially defines an example Poisson model class
/// type.
///
/// \brief declares and partially defines an example Poisson class type
//===----------------------------------------------------------------------===//

#ifndef EGCPP_POISSON_MODEL_H
#define EGCPP_POISSON_MODEL_H

#ifndef EGCPP
#include <egcpp>
#endif

/// An example namespace
namespace example {

/// \brief Poisson Model
class PoissonModel: LinearModel {
 public:
  /**
   * Given input/output data, constructs and fits a new PoissonModel:
   *
   * {{< katex display >}} \mathbf{y}_t = \exp\left(\mathbf{C} \mathbf{x}_{t} +
   * \mathbf{d}\right) {{< /katex >}}
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
   * @brief      Constructs and fits a new PoissonModel.
   *
   * @param      x     Input data [n_x x n_t]
   * @param      z     Measured output data [n_y x n_t]
   */
  PoissonModel(const arma::mat& x, const arma::mat& z);

  /**
   * Constructs a new PoissonModel from parameters:
   *
   * {{< katex display >}} \mathbf{y}_t = \exp \left( \mathbf{C} \mathbf{x}_{t} +
   * \mathbf{d}  \right) {{< /katex >}}
   *
   * {{< katex display >}} \mathbf{z}_t \sim \mathcal{N}\left(\mathbf{y}_t ,
   * \mathbf{R} \right) {{< /katex >}}
   *
   * where {{<katex>}} \mathbf{x}_{t} {{</katex>}}, {{<katex>}} \mathbf{y}_{t}
   * {{</katex>}}, and {{<katex>}} \mathbf{z}_{t} {{</katex>}} the input,
   * output, and measurement, respectively; {{<katex>}} \mathbf{C} {{</katex>}}
   * is the output matrix; {{<katex>}} \mathbf{d} {{</katex>}} is the output
   * bias.
   *
   * @brief      Constructs a new PoissonModel
   *
   * @param      C     output matrix
   * @param      d     output bias
   */
  PoissonModel(const arma::mat& C, const arma::vec& d);

  /**
   * @brief      simulates Poisson model
   *
   * @param      x          input data
   * @param      add_noise  whether to add measurement noise
   *
   * @return     model output
   */
  auto simulate(const arma::mat& x, bool add_noise = false) -> arma::mat;

 private:
  // Make this private.
  using LinearModel::LinearModel;
  using LinearModel::R;
};
}  // namespace example

#endif
