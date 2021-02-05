#ifndef EG_CPP_EXAMPLE_HPP
#define EG_CPP_EXAMPLE_HPP

// TODO(mfbolus): this is a fudge. I believe the include should never actually
// be called, but it allows clangd to resolve these symbols.
#ifndef EG_CPP
#include <eg_cpp>
#endif

/// An example namespace
namespace example {

/// An example class "Sys"
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

  /// adds argument to object field `x`.
  void add_to_x(const arma::vec& in);

 private:
  arma::mat A_;
  arma::mat C_;
  arma::vec x_;
  arma::vec y_;
};

/// modifies input mat in-place
void ChangeMat(arma::mat& X);

}  // namespace example

#endif
