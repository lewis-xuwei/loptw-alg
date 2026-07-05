///======================================================
/// Project :   loptw-alg
/// File    :   solution.cpp
///------------------------------------------------------
/// Time    :   2026/07/05 15:51:26
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/solution.h>

namespace loptw::alg {

Solution::Solution(std::shared_ptr<instance::Instance> inst, std::shared_ptr<Parameter> parameter) :
  inst_{inst}, parameter_{parameter} {}

// Calculate the objective
double Solution::Objective() const {
  return obj_;
}

// Print the result
void Solution::PrintResult() const {}

bool Solution::operator<(const Solution& solution) const {
  return obj_ < solution.obj_;
}

std::shared_ptr<Solution> Solution::Copy() {
  return std::make_shared<Solution>(*this);
}

} // namespace loptw::alg
