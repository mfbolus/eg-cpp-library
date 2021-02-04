#ifndef LDS_SYS_HPP
#define LDS_SYS_HPP

#include <armadillo>

/// A namespace for linear dynamical systems.
namespace lds {

/// A system object for linear dynamical systems.
class Sys {
 public:
  Sys(size_t n_x, size_t n_y);
  // ~Sys() = default;

  auto A() const -> arma::mat { return A_; }
  auto C() const -> arma::mat { return C_; }
  auto x() const -> arma::vec { return x_; }
  auto y() const -> arma::vec { return y_; }

  /// adds argument to underlying state of system.
  void add_to_x(const arma::vec& in);

 private:
  arma::mat A_;
  arma::mat C_;
  arma::vec x_;
  arma::vec y_;
};

/// modifies input mat in-place
void ChangeMat(arma::mat& X);

}  // namespace lds

#endif
