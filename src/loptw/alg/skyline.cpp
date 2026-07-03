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

std::vector<std::vector<double>> Skylines::Merge(std::vector<Skyline>& skylines) {
  std::sort(skylines.begin(), skylines.end(), [](const Skyline& a, const Skyline& b) {
    return a.left < b.left;
  });
  auto cmp = [](const std::pair<double, double>& a, const std::pair<double, double>& b) -> bool {
    return a.second < b.second;
  };
  std::
    priority_queue<std::pair<double, double>, std::vector<std::pair<double, double>>, decltype(cmp)>
      que(cmp);

  std::vector<double> boundaries;
  for (auto& skyline : skylines) {
    boundaries.emplace_back(skyline.left);
    boundaries.emplace_back(skyline.right);
  }
  std::sort(boundaries.begin(), boundaries.end());

  std::vector<std::vector<double>> ret;
  int n = skylines.size(), idx = 0;
  for (auto& boundary : boundaries) {
    while (idx < n && skylines[idx].left <= boundary) {
      que.emplace(skylines[idx].right, skylines[idx].height);
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

bool Skylines::Locate(const std::vector<Skyline>& skylines,
                      double width,
                      double height,
                      double H,
                      int index) {
  if (H - skylines[index].height < height) {
    return false;
  }

  for (int i = index; i < skylines.size() && width > 0; i++) {
    double curr_width = skylines[i].right - skylines[i].left;
    if (curr_width >= width) {
      return true;
    } else if (i < skylines.size() - 1 && skylines[i + 1].height <= skylines[index].height) {
      width -= curr_width;
    } else {
      return false;
    }
  }

  return false;
}

void Skylines::MergeSkyline(std::vector<Skyline>& skylines, double x_start, double x_end) {
  std::vector<std::vector<double>> ret = Merge(skylines);
  std::vector<Skyline> merged_skylines;
  for (int i = 0; i < ret.size() - 1; i++) {
    double left = ret[i][0];
    double height = ret[i][1];
    double right = ret[i + 1][0];

    merged_skylines.push_back(Skyline{left, right, height});
  }

  if (ret.front()[0] > x_start) {
    merged_skylines.insert(merged_skylines.begin(), Skyline{x_start, ret.front()[0], 0});
  }

  if (ret.back()[0] < x_end) {
    merged_skylines.push_back(Skyline{ret.back()[0], x_end, 0});
  }

  skylines = merged_skylines;
}

} // namespace loptw::alg