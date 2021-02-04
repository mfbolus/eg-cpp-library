#include <lds_sys.hpp>

namespace lds {
Sys::Sys(size_t n_x, size_t n_y) {
  x_ = arma::zeros(n_x);
  y_ = arma::zeros(n_y);
  A_ = arma::zeros(n_x, n_y);
  C_ = arma::zeros(n_y, n_x);
}

void Sys::add_to_x(const arma::vec &in) { x_ += in; }

void ChangeMat(arma::mat &X) { X(0) = 1.0; }
}  // namespace lds
