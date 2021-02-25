//===-- main.cpp - Example Program ----------------------------------------===//
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
/// This file provides an example for library usage.
///
/// \brief provides example for library usage
//===----------------------------------------------------------------------===//

#include <egcpp>

auto main() -> int {
  std::cout << "\n\nTesting example library by fitting a model by linear "
               "regression.\n";

  size_t n_t(100000);  // number of time steps
  const size_t n_x = 2;
  const size_t n_y = 1;

  arma::mat c_true(n_y, n_x, arma::fill::zeros);
  c_true(0) = 0.25;
  c_true(1) = 1 - c_true(0);

  arma::vec d_true(n_y, arma::fill::zeros);
  d_true(0) = 0.5;

  arma::mat r_true(n_y, n_y, arma::fill::eye);
  r_true *= 1e-1;

  example::LinearRegressionModel model_true(c_true, d_true, r_true);

  // generate the data.
  arma::vec x0(n_x, arma::fill::zeros);    // initial condition
  arma::mat q(n_x, n_x, arma::fill::eye);  // process noise for random walk
  q *= 1e-1;
  arma::mat x = example::random_walk(n_t, q, x0);  // random input data
  auto z = model_true.simulate(x, true);

  // fit data
  std::cout << "\nFitting model to " << n_t << " samples of input data ...\n";
  auto start = std::chrono::high_resolution_clock::now();
  example::LinearRegressionModel model_est(x, z);
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> fit_time_ms = finish - start;
  std::cout << "Finished in " << fit_time_ms.count() << " ms.\n";

  // simulate the newly fit model
  auto y_hat = model_est.simulate(x);
  auto e = z - y_hat;
  arma::vec p_ve = arma::vec(n_y).ones() - arma::var(e, 0, 1) / arma::var(z, 0, 1);

  std::cout << "\nC_true = \n" << c_true << "\n";
  std::cout << "C_est = \n" << model_est.C() << "\n";

  std::cout << "d_true = \n" << d_true << "\n";
  std::cout << "d_est = \n" << model_est.d() << "\n";

  std::cout << "R_true = \n" << r_true << "\n";
  std::cout << "R_est = \n" << model_est.R() << "\n";

  std::cout << "prop. variance explained: \n" << p_ve << "\n";
  return 0;
}
