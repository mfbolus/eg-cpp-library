---
title: example::LinearRegressionModel
summary: Linear Regression Model. 

---

# example::LinearRegressionModel



Linear Regression Model. 
`#include <linear_regression_model.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[LinearRegressionModel](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#function-linearregressionmodel)**(const arma::mat & x, const arma::mat & z)<br>Constructs and fits a new [LinearRegressionModel](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/).  |
| | **[LinearRegressionModel](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#function-linearregressionmodel)**(const arma::mat & C, const arma::vec & d, const arma::mat & R)<br>Constructs a new [LinearRegressionModel](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/).  |
| auto | **[C](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#function-c)**() const<br>get output matrix (C)  |
| auto | **[d](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#function-d)**() const<br>get output bias (d)  |
| auto | **[R](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#function-r)**() const<br>get measurement noise covariance (R)  |
| auto | **[simulate](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#function-simulate)**(const arma::mat & x, bool add_noise =false)<br>simulates linear regression model  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| const size_t | **[n_x](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#variable-n_x)** <br>number of input channels  |
| const size_t | **[n_y](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/#variable-n_y)** <br>number of output channels  |

## Public Functions Documentation

### function LinearRegressionModel

```cpp
LinearRegressionModel(
    const arma::mat & x,
    const arma::mat & z
)
```

Constructs and fits a new [LinearRegressionModel](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/). 

**Parameters**: 

  * **x** Input data [n_x x n_t] 
  * **z** Measured output data [n_y x n_t] 


Given input/output data, constructs and fits a new Linear Regression Model:

y = C*x + d

z ~ N(y, R)


### function LinearRegressionModel

```cpp
LinearRegressionModel(
    const arma::mat & C,
    const arma::vec & d,
    const arma::mat & R
)
```

Constructs a new [LinearRegressionModel](/eg-cpp-library/classes/classexample_1_1_linear_regression_model/). 

**Parameters**: 

  * **C** output matrix 
  * **d** output bias 
  * **R** measurement noise covariance 


Constructs a new Linear Regression Model from parameters:

y = C*x + d

z ~ N(y, R)


### function C

```cpp
inline auto C() const
```

get output matrix (C) 

### function d

```cpp
inline auto d() const
```

get output bias (d) 

### function R

```cpp
inline auto R() const
```

get measurement noise covariance (R) 

### function simulate

```cpp
auto simulate(
    const arma::mat & x,
    bool add_noise =false
)
```

simulates linear regression model 

**Parameters**: 

  * **x** input data 
  * **add_noise** whether to add measurement noise


**Return**: model output 

## Public Attributes Documentation

### variable n_x

```cpp
const size_t n_x;
```

number of input channels 

### variable n_y

```cpp
const size_t n_y;
```

number of output channels 

-------------------------------

Updated on 25 February 2021 at 13:11:34 CST