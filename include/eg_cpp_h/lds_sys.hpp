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

  /// get A
  auto A() const -> arma::mat const& { return A_; }
  /// set A
  void A(arma::mat const& A);

  /// get C
  auto C() const -> arma::mat const& { return C_; }
  /// set C
  void C(arma::mat const& C) { C_ = C; }

  auto x() const -> arma::vec const& { return x_; }
  auto y() const -> arma::vec const& { return y_; }

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
