///======================================================
/// Project :   loptw-alg
/// File    :   tabulist.h
///------------------------------------------------------
/// Time    :   2026/07/05 15:05:40
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <vector>

namespace loptw::alg {

class TabuList {
public:
  TabuList();
  TabuList(int size, int tenure);

  void AddTabu(int i, int j);
  bool Tabued(int i, int j);
  void Update();

private:
  int size_;                                // n*n的禁忌表
  int tenure_;                              // 禁忌期
  std::vector<std::vector<int>> tabu_list_; // 禁忌表
};

} // namespace loptw::alg
