///======================================================
/// Project :   loptw-alg
/// File    :   skyline.cpp
///------------------------------------------------------
/// Time    :   2026/07/02 17:03:57
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/skyline.h>

namespace loptw::alg {

std::vector<std::vector<double>> SkylineMerger::Merge(std::vector<Skyline>& buildings) {
  std::sort(buildings.begin(), buildings.end(), [](const Skyline& a, const Skyline& b) {
    return a.left < b.left;
  });
  auto cmp = [](const std::pair<double, double>& a, const std::pair<double, double>& b) -> bool {
    return a.second < b.second;
  };
  std::
    priority_queue<std::pair<double, double>, std::vector<std::pair<double, double>>, decltype(cmp)>
      que(cmp);

  std::vector<double> boundaries;
  for (auto& building : buildings) {
    boundaries.emplace_back(building.left);
    boundaries.emplace_back(building.right);
  }
  std::sort(boundaries.begin(), boundaries.end());

  std::vector<std::vector<double>> ret;
  int n = buildings.size(), idx = 0;
  for (auto& boundary : boundaries) {
    while (idx < n && buildings[idx].left <= boundary) {
      que.emplace(buildings[idx].right, buildings[idx].height);
      idx++;
    }
    while (!que.empty() && que.top().first <= boundary) {
      que.pop();
    }

    double maxn = que.empty() ? 0 : que.top().second;
    if (ret.size() == 0 || maxn != ret.back()[1]) {
      ret.push_back({boundary, maxn});
    }
  }
  return ret;
}

} // namespace loptw::alg