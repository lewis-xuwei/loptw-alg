///======================================================
/// Project :   loptw-alg
/// File    :   tabusearch.h
///------------------------------------------------------
/// Time    :   2026/07/06 09:09:19
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_ALG_TABUSEARCH_H__
#define __LOPTW_ALG_INCLUDE_LOPTW_ALG_TABUSEARCH_H__

#include <memory>

#include <loptw/alg/parameter.h>
#include <loptw/alg/solution.h>
#include <loptw/alg/tabulist.h>
#include <loptw/instance/instance.h>
#include <loptw/utility/timer.h>

namespace loptw::alg {

class TabuSearch {
public:
  TabuSearch(std::shared_ptr<instance::Instance> inst, std::shared_ptr<Parameter> para);

  std::shared_ptr<Solution> Initialization(); // 解的初始化

  void Run(); // 迭代过程

private:
  std::shared_ptr<instance::Instance> inst_;
  std::shared_ptr<Parameter> para_;
  int T;
  int N;
  int F;

private:
  std::shared_ptr<TabuList> tabu_list_;
  loptw::utility::Timer timer_;
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_TABUSEARCH_H__
