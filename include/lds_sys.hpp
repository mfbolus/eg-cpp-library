#ifndef LDS_SYS_HPP
#define LDS_SYS_HPP

#include <armadillo>

namespace lds {
class Sys {
 public:
  Sys(size_t n_x, size_t n_y);
  ~Sys();

  void add_to_x(const arma::vec& x);

 private:
  arma::mat A_;
  arma::mat C_;
  arma::vec x_;
  arma::vec y_;
};

void Change_A(arma::mat& A);

}  // namespace lds

#endif
