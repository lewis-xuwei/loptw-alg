

#include <loptw/alns/Statistics.h>

void Statistics::initOptCounts(const std::string& optString) {
  _optUsageMap[optString] = std::array<int, 4>{0, 0, 0, 0};
}

void Statistics::addOptCounts(const std::string& optString, int weight_idx) {
  _optUsageMap[optString][weight_idx] += 1;
}

void Statistics::collectObjective(double current,
                                  double candidate,
                                  double best) {
  _objectives.push_back({current, candidate, best});
}

void Statistics::printOptUsage() {
  for (const auto& i : _optUsageMap) {
    std::cout << i.first.substr(0, 6) << ":[";
    for (const auto j : i.second) {
      std::cout << j << ",";
    }
    std::cout << "]; ";
  }
}

void Statistics::saveObjective(const std::string& save_path) {
  std::ofstream objFile;
  objFile.open(save_path);
  objFile << "iteration, current, candidate, best" << std::endl;
  for (unsigned i = 0; i < _objectives.size(); ++i) {
    objFile << i << ", " << _objectives[i][0] << ", " << _objectives[i][1]
            << ", " << _objectives[i][2] << std::endl;
  }
  objFile.close();
}

void Statistics::saveOptUsage(const std::string& save_path) {
  std::ofstream optUsageFile;
  optUsageFile.open(save_path);
  optUsageFile << "opt_name, ";
  for (auto& i : _optUsageMap) {
    optUsageFile << i.first << ", ";
  }
  optUsageFile << std::endl;
  for (unsigned i = 0; i < _optIterationUsageMap.size(); ++i) {
    const auto& optUsage = _optIterationUsageMap[i];
    // iteration
    optUsageFile << i << ", ";
    for (const auto& j : optUsage) {
      for (const auto& k : j.second) {
        optUsageFile << k << ";";
      }
      optUsageFile << ", ";
    }
    optUsageFile << std::endl;
  }
  optUsageFile.close();
}

void Statistics::updateOptUsageMap() {
  _optIterationUsageMap.push_back(_optUsageMap);
}
