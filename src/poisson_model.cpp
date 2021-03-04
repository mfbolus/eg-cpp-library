//===-- poisson_model.cpp - Poisson Model Class ---------------------------===//
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
/// This file defines an example Poisson model class type.
///
/// \brief defines an example Poisson model class type
//===----------------------------------------------------------------------===//

#include <egcpp>

namespace example {

PoissonModel::PoissonModel(const arma::mat& x, const arma::mat& z)
    : LinearModel(x, z) {}

PoissonModel::PoissonModel(const arma::mat& C, const arma::vec& d)
    : LinearModel(C, d,
                            arma::mat(d.n_elem, d.n_elem, arma::fill::zeros)) {}

auto PoissonModel::simulate(const arma::mat& x, bool add_noise) -> arma::mat {
  size_t n_t(x.n_cols);  // number of time samples
  arma::mat y_hat(n_y, n_t);

  y_hat = C_ * x;
  y_hat.each_col() += d_;
  y_hat = arma::exp(y_hat);  // exponential nonlinearity

  if (add_noise) {
    for (size_t t = 0; t < n_t; t++) {
      arma::vec chance(n_y, arma::fill::randu);
      for (size_t p = 0; p < n_y; p++) {
        y_hat.col(t)[p] = (y_hat.col(t)[p] > chance[p]) ? 0.0 : 1.0;
      }
    }
  }

  return y_hat;
}

}  // namespace example
