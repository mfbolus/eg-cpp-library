---
title: egcpp_h/random_walk.h
summary: declares a random walk simulation 

---

# egcpp_h/random_walk.h

declares a random walk simulation  [More...](#detailed-description)



## Namespaces

| Name           |
| -------------- |
| **[example](/eg-cpp-library/docs/api/namespaces/namespaceexample/)** <br>An example namespace.  |

## Detailed Description



This file declares a random walk simulation. 





## Source code

```cpp
//===-- egcpp_h/random_walk.h - Random Walk ---------------------*- C++ -*-===//
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

#ifndef EGCPP_RANDOM_WALK_H
#define EGCPP_RANDOM_WALK_H

// TODO(mfbolus): this is a fudge. I believe the include should never actually
// be called, but it allows clangd to resolve these symbols.
#ifndef EGCPP
#include <egcpp>
#endif

namespace example {

auto random_walk(size_t n_t, const arma::mat& Q, arma::vec x0) -> arma::mat;

}  // namespace example

#endif
```


-------------------------------

Updated on 26 February 2021 at 23:25:30 CST
