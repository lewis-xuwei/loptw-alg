///======================================================
/// Project :   loptw-alg
/// File    :   tabulist.cpp
///------------------------------------------------------
/// Time    :   2026/07/05 15:11:30
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/tabulist.h>

namespace loptw::alg {

TabuList::TabuList() {}

TabuList::TabuList(int size, int tenure) : size_{size}, tenure_{tenure} {
  tabu_list_.reserve(size_);
  for (size_t i = 0; i < size; i++) {
    tabu_list_.push_back(std::vector<int>(size_, 0));
  }
}

void TabuList::AddTabu(int i, int j) {
  tabu_list_[i][j] = tenure_;
}

bool TabuList::Tabued(int i, int j) {
  return tabu_list_[i][j] != 0;
}

void TabuList::Update() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (tabu_list_[i][j] > 0) {
        tabu_list_[i][j]--;
      }
    }
  }
}

} // namespace loptw::alg
