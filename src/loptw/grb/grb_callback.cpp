///======================================================
/// Project :   loptw-alg
/// File    :   grb_callback.cpp
///------------------------------------------------------
/// Time    :   2026/07/04 14:48:01
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/grb/grb_callback.h>

namespace loptw::grb {

CoverInequality::CoverInequality(std::shared_ptr<instance::Instance> inst,
                                 std::vector<std::vector<GRBVar>>& z) :
  inst(inst), z(z) {
  T = inst->GetNumBuildings();
  N = inst->GetNumTaskNodes();
  F = inst->GetNumWorkflows();
}

void CoverInequality::callback() {
  try {
    if (where == GRB_CB_MIPSOL) {
      // Get the current solution
      std::vector<std::vector<double>> z_sol(N, std::vector<double>(T));
      for (int i = 0; i < N; ++i) {
        for (int t = 0; t < T; ++t) {
          z_sol[i][t] = getSolution(z[i][t]);
        }
      }

      for (int t = 0; t < T; ++t) {
        std::vector<int> cover_set;
        for (int i = 0; i < N; ++i) {
          if (z_sol[i][t] > 0.5) {
            cover_set.push_back(i);
          }
        }

        double sum_of_area = 0.0;
        for (int i : cover_set) {
          double w_i = inst->tasknodes().at(i)->width_;
          double h_i = inst->tasknodes().at(i)->length_;
          sum_of_area += w_i * h_i;
        }
        double building_area = inst->buildings().at(t)->width_ * inst->buildings().at(t)->length_;
        if (sum_of_area > building_area) {
          GRBLinExpr expr;
          for (int i : cover_set) {
            expr += z[i][t];
          }
          addLazy(expr <= cover_set.size() - 1);
          std::cout << "Cover Inequality Callback: add a new cut." << std::endl;
        }
      }
    }
  } catch (GRBException e) {
    std::cout << "Error number: " << e.getErrorCode() << std::endl;
    std::cout << e.getMessage() << std::endl;
  } catch (...) {
    std::cout << "Error during callback" << std::endl;
  }
}

} // namespace loptw::grb