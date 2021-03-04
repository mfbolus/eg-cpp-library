---
title: example
summary: An example namespace. 

---

# example

An example namespace. <br>

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[example::LinearModel](/eg-cpp-library/docs/api/classes/classexample_1_1_linear_model/)** <br>Linear Regression Model.  |
| class | **[example::PoissonModel](/eg-cpp-library/docs/api/classes/classexample_1_1_poisson_model/)** <br>Poisson Model.  |

## Functions

|                | Name           |
| -------------- | -------------- |
| auto | **[random_walk](/eg-cpp-library/docs/api/namespaces/namespaceexample/#function-random_walk)**(size_t n_t, const arma::mat & Q, arma::vec x0)<br>simulates random walk  |


## Function Details

### random_walk

```cpp
auto random_walk(
    size_t n_t,
    const arma::mat & Q,
    arma::vec x0
)
```



**Parameters**:

  * **n_t** number of time samples 
  * **Q** process noise covariance 
  * **x0** initial value


**Return**: random variable 






-------------------------------

Updated on  4 March 2021 at 09:55:16 CST
