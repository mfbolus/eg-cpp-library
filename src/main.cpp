#include <iostream>
#include <lds_sys.hpp>
#include <ostream>

auto main(int argc, char const *argv[]) -> int {
  std::cout << "nargs = " << argc << std::endl;
  if (argv) {
    std::cout << "argv = " << argv << std::endl;
  }

  const size_t n_x = 2;
  size_t n_y = 4;
  lds::Sys sys(n_x, n_y);
  auto a = sys.A();
  auto x = sys.x();

  std::cout << "A: \n" << a << std::endl;
  std::cout << "x: \n" << x << std::endl;

  // muck about with the data and reprint
  lds::ChangeMat(a);

  x += arma::vec(n_x).ones();
  sys.add_to_x(x);
  x = sys.x();

  std::cout << "A: \n" << a << std::endl;
  std::cout << "x: \n" << x << std::endl;

  return 0;
}
