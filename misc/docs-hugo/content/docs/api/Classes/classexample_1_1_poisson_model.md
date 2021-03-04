---
title: example::PoissonModel
summary: Poisson Model. 

---

# example::PoissonModel



Poisson Model. 
<br /> `#include <poisson_model.h>`

Inherits from [example::LinearModel](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/#function-poissonmodel)**(const arma::mat & x, const arma::mat & z)<br>Constructs and fits a new [PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/).  |
| | **[PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/#function-poissonmodel)**(const arma::mat & C, const arma::vec & d)<br>Constructs a new [PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/).  |
| auto | **[simulate](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/#function-simulate)**(const arma::mat & x, bool add_noise =false)<br>simulates Poisson model  |

## Additional inherited members

**Public Functions inherited from [example::LinearModel](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/)**

|                | Name           |
| -------------- | -------------- |
| auto | **[C](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/#function-c)**() const<br>get output matrix (C)  |
| auto | **[d](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/#function-d)**() const<br>get output bias (d)  |

**Public Attributes inherited from [example::LinearModel](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/)**

|                | Name           |
| -------------- | -------------- |
| const size_t | **[n_x](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/#variable-n_x)** <br>number of input channels  |
| const size_t | **[n_y](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/#variable-n_y)** <br>number of output channels  |

**Protected Attributes inherited from [example::LinearModel](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/)**

|                | Name           |
| -------------- | -------------- |
| arma::mat | **[C_](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/#variable-c_)** <br>output matrix  |
| arma::vec | **[d_](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/#variable-d_)** <br>output bias  |


---
---
## Public Function Details

### **PoissonModel**

```cpp
PoissonModel(
    const arma::mat & x,
    const arma::mat & z
)
```



**Parameters**:

  * **x** Input data [n_x x n_t] 
  * **z** Measured output data [n_y x n_t] 


Given input/output data, constructs and fits a new [PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/):

{{< katex display >}} \mathbf{y}_t = \exp\left(\mathbf{C} \mathbf{x}_{t} + \mathbf{d}\right) {{< /katex >}}

{{< katex display >}} \mathbf{z}_t \sim \mathcal{N}\left(\mathbf{y}_t , \mathbf{R} \right) {{< /katex >}}

where {{<katex>}} \mathbf{x}_{t} {{</katex>}}, {{<katex>}} \mathbf{y}_{t} {{</katex>}}, and {{<katex>}} \mathbf{z}_{t} {{</katex>}} the input, output, and measurement, respectively; {{<katex>}} \mathbf{C} {{</katex>}} is the output matrix; {{<katex>}} \mathbf{d} {{</katex>}} is the output bias; and {{<katex>}} \mathbf{R} {{</katex>}} is the covariance of the assumed Gaussian measurement noise.


---
### **PoissonModel**

```cpp
PoissonModel(
    const arma::mat & C,
    const arma::vec & d
)
```



**Parameters**:

  * **C** output matrix 
  * **d** output bias 


Constructs a new [PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/) from parameters:

{{< katex display >}} \mathbf{y}_t = \exp \left( \mathbf{C} \mathbf{x}_{t} + \mathbf{d} \right) {{< /katex >}}

{{< katex display >}} \mathbf{z}_t \sim \mathcal{N}\left(\mathbf{y}_t , \mathbf{R} \right) {{< /katex >}}

where {{<katex>}} \mathbf{x}_{t} {{</katex>}}, {{<katex>}} \mathbf{y}_{t} {{</katex>}}, and {{<katex>}} \mathbf{z}_{t} {{</katex>}} the input, output, and measurement, respectively; {{<katex>}} \mathbf{C} {{</katex>}} is the output matrix; {{<katex>}} \mathbf{d} {{</katex>}} is the output bias.


---
### **simulate**

```cpp
auto simulate(
    const arma::mat & x,
    bool add_noise =false
)
```



**Parameters**:

  * **x** input data 
  * **add_noise** whether to add measurement noise


**Return**: model output 

---


-------------------------------

Updated on  4 March 2021 at 09:55:16 CST
