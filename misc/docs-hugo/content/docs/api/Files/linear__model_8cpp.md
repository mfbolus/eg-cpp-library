---
title: src/linear_model.cpp
summary: defines an example linear model class type 

---

# src/linear_model.cpp

defines an example linear model class type  [More...](#detailed-description)



## Namespaces

| Name           |
| -------------- |
| **[example](/eg-cpp-library/docs/api/namespaces/namespaceexample/)** <br>An example namespace.  |

## Detailed Description



This file defines an example linear model class type. 





## Source code

```cpp
//===-- linear_model.cpp - Linear Model Class -----------------------------===//
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
//===----------------------------------------------------------------------===//

#include <egcpp>

namespace example {

LinearModel::LinearModel(const arma::mat& x,
                                             const arma::mat& z)
    : n_x(x.n_rows),
      n_y(z.n_rows),
      C_(arma::mat(n_y, n_x, arma::fill::zeros)),
      d_(arma::vec(n_y, arma::fill::zeros)),
      R_(arma::mat(n_y, n_y, arma::fill::zeros)) {
  size_t n_t(x.n_cols);  // number of time samples

  // solve for C+d:
  arma::mat sum_zx(n_y, n_x + 1, arma::fill::zeros);
  arma::vec x1(n_x + 1, arma::fill::zeros);
  x1[n_x] = 1.0;

  // covariance of input data
  arma::mat sum_x1_x1(n_x + 1, n_x + 1, arma::fill::zeros);

  for (size_t t = 1; t < n_t; t++) {
    x1.subvec(0, n_x - 1) = x.col(t);
    sum_zx += z.col(t) * x1.t();
    sum_x1_x1 += x1 * x1.t();
    // if input x were *not* deterministic and had own covar, P
    // sum_E_x1_x1.submat(0, 0, n_x - 1, n_x - 1) += P.slice(t);
  }

  arma::mat Cd = sum_zx * arma::inv_sympd(sum_x1_x1);
  C_ = Cd.submat(0, 0, n_y - 1, n_x - 1);
  d_ = vectorise(Cd.submat(0, n_x, n_y - 1, n_x));

  // Ghahgramani, Hinton 1996:
  arma::mat sum_zz(n_y, n_y, arma::fill::zeros);
  arma::mat sum_yz(n_y, n_y, arma::fill::zeros);
  for (size_t t = 1; t < n_t; t++) {
    sum_zz += z.col(t) * z.col(t).t();
    sum_yz += (C_ * x.col(t) + d_) * z.col(t).t();
  }
  R_ = (sum_zz - sum_yz) / n_t;
}

LinearModel::LinearModel(const arma::mat& C,
                                             const arma::vec& d,
                                             const arma::mat& R)
    : n_x(C.n_cols),
      n_y(C.n_rows),
      C_(arma::mat(n_y, n_x, arma::fill::zeros)),
      d_(arma::vec(n_y, arma::fill::zeros)),
      R_(arma::mat(n_y, n_y, arma::fill::zeros)) {
  C_ = C;
  d_ = d;
  R_ = R;
}

auto LinearModel::simulate(const arma::mat& x, bool add_noise)
    -> arma::mat {
  size_t n_t(x.n_cols);  // number of time samples
  arma::mat y_hat(n_y, n_t);

  y_hat = C_ * x;
  y_hat.each_col() += d_;

  if (add_noise) {
    y_hat += arma::mvnrnd(arma::vec(n_y).fill(0), R_, n_t);
  }

  return y_hat;
}

}  // namespace example
```


-------------------------------

Updated on  4 March 2021 at 09:51:17 CST
