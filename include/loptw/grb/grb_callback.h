///======================================================
/// Project :   loptw-alg
/// File    :   grb_callback.h
///------------------------------------------------------
/// Time    :   2026/07/04 14:38:49
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_GRB_GRB_CALLBACK_H__
#define __LOPTW_ALG_INCLUDE_LOPTW_GRB_GRB_CALLBACK_H__

#include <loptw/instance/instance.h>

#include "gurobi_c++.h"

namespace loptw::grb {

class CoverInequality : public GRBCallback {
public:
  CoverInequality(std::shared_ptr<instance::Instance> inst, std::vector<std::vector<GRBVar>>& z);

protected:
  void callback() override;

private:
  std::shared_ptr<instance::Instance> inst;
  int T;
  int N;
  int F;

private:
  std::vector<std::vector<GRBVar>> z; // z[N][T]
};

} // namespace loptw::grb

#endif // __LOPTW_ALG_INCLUDE_LOPTW_GRB_GRB_CALLBACK_H__
