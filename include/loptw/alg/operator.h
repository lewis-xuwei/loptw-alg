///======================================================
/// Project :   loptw-alg
/// File    :   operator.h
///------------------------------------------------------
/// Time    :   2026/07/05 15:20:06
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_ALG_OPERATOR_H__
#define __LOPTW_ALG_INCLUDE_LOPTW_ALG_OPERATOR_H__

#include <memory>
#include <string>

#include <loptw/alg/solution.h>
#include <loptw/alg/tabulist.h>

namespace loptw::alg {

class Operator {
public:
  Operator(std::string name, double priority);
  virtual ~Operator() = default;

  virtual std::shared_ptr<Solution> Opt(const std::shared_ptr<Solution>& solution,
                                        const double bestCost,
                                        std::shared_ptr<TabuList> tabulist) = 0;
  virtual void AddTabu(std::shared_ptr<TabuList> tabulist) = 0;
  virtual void ResetTabu() = 0;
  virtual void ShowTabu() = 0;

  virtual double priority() const;
  virtual void priority(double priority);
  virtual std::string name() const;

private:
  std::string name_; // 算子类型
  double priority_;  // 算子权重
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_OPERATOR_H__
