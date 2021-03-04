---
title: src/random_walk.cpp
summary: defines a random walk simulation 

---

# src/random_walk.cpp

defines a random walk simulation  [More...](#detailed-description)



## Namespaces

| Name           |
| -------------- |
| **[example](/eg-cpp-library/docs/api/namespaces/namespaceexample/)** <br>An example namespace.  |

## Detailed Description



This file defines a random walk simulation. 





## Source code

```cpp
//===-- random_walk.cpp - Random Walk -------------------------------------===//
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

auto random_walk(size_t n_t, const arma::mat& Q, arma::vec x0) -> arma::mat {
  size_t n_x = Q.n_rows;

  if ((n_x != Q.n_cols) || (Q.n_cols != Q.n_rows)) {
    throw std::logic_error("Q must be `n_x` x `n_x`.");
  }

  arma::mat x(n_x, n_t, arma::fill::zeros);
  x.col(0) = x0;
  for (size_t t = 1; t < n_t; t++) {
    x.col(t) =
        x.col(t - 1) + arma::mvnrnd(arma::vec(n_x, arma::fill::zeros), Q);
  }

  return x;
}

}  // namespace example
```


-------------------------------

Updated on  4 March 2021 at 09:51:18 CST
