---
title: egcpp_h/poisson_model.h
summary: declares and partially defines an example Poisson class type 

---

# egcpp_h/poisson_model.h

declares and partially defines an example Poisson class type  [More...](#detailed-description)



## Namespaces

| Name           |
| -------------- |
| **[example](/eg-cpp-library/docs/api/namespaces/namespaceexample/)** <br>An example namespace.  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[example::PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/)** <br>Poisson Model.  |

## Detailed Description



This file declares and partially defines an example Poisson model class type. 





## Source code

```cpp
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
//===----------------------------------------------------------------------===//

#ifndef EGCPP_POISSON_MODEL_H
#define EGCPP_POISSON_MODEL_H

#ifndef EGCPP
#include <egcpp>
#endif

namespace example {

class PoissonModel: LinearModel {
 public:
  PoissonModel(const arma::mat& x, const arma::mat& z);

  PoissonModel(const arma::mat& C, const arma::vec& d);

  auto simulate(const arma::mat& x, bool add_noise = false) -> arma::mat;

 private:
  // Make this private.
  using LinearModel::LinearModel;
  using LinearModel::R;
};
}  // namespace example

#endif
```


-------------------------------

Updated on 26 February 2021 at 23:25:30 CST
