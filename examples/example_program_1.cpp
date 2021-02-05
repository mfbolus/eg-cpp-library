#include <eg_cpp>
#include <iostream>
#include <ostream>

auto main(int argc, char const *argv[]) -> int {
  std::cout << "nargs = " << argc << std::endl;
  if (argv) {
    std::cout << "argv = " << argv << std::endl;
  }

  const size_t n_x = 2;
  size_t n_y = 4;
  example::Sys sys(n_x, n_y);
  auto a_0 = sys.A();
  auto x_0 = sys.x();
  auto c_0 = sys.C();

  std::cout << "Original values for A, x, C : \n";
  std::cout << "A: \n" << a_0 << std::endl;
  std::cout << "x: \n" << x_0 << std::endl;
  std::cout << "C: \n" << c_0 << std::endl;

  // muck about with the data and reprint
  example::ChangeMat(a_0);
  auto a_1 = sys.A();

  x_0 += arma::vec(n_x).ones();
  sys.add_to_x(x_0);
  x_0 = sys.x();

  std::cout << "A (modified): \n" << a_0 << std::endl;
  std::cout << "x (modified): \n" << x_0 << std::endl;

  sys.A(a_0);
  a_1 = sys.A();
  // std::cout << "A_1: \n" << a_1 << std::endl;

  std::cout << "This shows simple handling of size mismatch in set method.\n";
  auto a_2 = arma::mat(1, 1).zeros();
  sys.A(a_2);

  std::cout << "This shows danger of *not* checking size in set method.\n";
  auto c_1 = arma::mat(1, 2).zeros();
  sys.C(c_1);
  auto c_2 = sys.C();
  std::cout << "C_0 \n" << c_0 << "\n";
  std::cout << "C_1 \n" << c_1 << "\n";
  std::cout << "C_2: \n" << c_2 << "\n";

  return 0;
}
