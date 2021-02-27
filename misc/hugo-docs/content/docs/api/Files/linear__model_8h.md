---
title: egcpp_h/linear_model.h
summary: declares and partially defines an example linear model class type 

---

# egcpp_h/linear_model.h

declares and partially defines an example linear model class type  [More...](#detailed-description)



## Namespaces

| Name           |
| -------------- |
| **[example](/eg-cpp-library/docs/api/namespaces/namespaceexample/)** <br>An example namespace.  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[example::LinearModel](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/)** <br>Linear Regression Model.  |

## Detailed Description



This file declares and partially defines an example linear model class type. 





## Source code

```cpp
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
//===----------------------------------------------------------------------===//

#ifndef EGCPP_LINEAR_MODEL_H
#define EGCPP_LINEAR_MODEL_H

// this is just here so clangd can resolve these symbols.
#ifndef EGCPP
#include <egcpp>
#endif

namespace example {

class LinearModel {
 public:
  LinearModel(const arma::mat& x, const arma::mat& z);

  LinearModel(const arma::mat& C, const arma::vec& d,
                        const arma::mat& R);

  auto C() const -> const arma::mat& { return C_; }

  auto d() const -> const arma::vec& { return d_; }

  auto R() const -> const arma::mat& { return R_; }

  auto simulate(const arma::mat& x, bool add_noise = false) -> arma::mat;

  const size_t n_x;  
  const size_t n_y;  

 protected:
  arma::mat C_;  
  arma::vec d_;  

private:
  arma::mat R_;  
};
}  // namespace example

#endif
```


-------------------------------

Updated on 26 February 2021 at 23:25:30 CST
