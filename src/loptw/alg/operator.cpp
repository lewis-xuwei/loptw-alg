///======================================================
/// Project :   loptw-alg
/// File    :   operator.cpp
///------------------------------------------------------
/// Time    :   2026/07/05 15:35:20
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/operator.h>

namespace loptw::alg {

Operator::Operator(std::string name, double priority) : name_{name}, priority_{priority} {}

double Operator::priority() const {
  return priority_;
}

void Operator::priority(double priority) {
  priority_ = priority;
}

std::string Operator::name() const {
  return name_;
}

} // namespace loptw::alg
