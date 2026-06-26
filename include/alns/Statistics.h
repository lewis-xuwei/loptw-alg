
#ifndef ALNS_STATISTICS_H
#define ALNS_STATISTICS_H

#include <alns/headers.h>

namespace alns {

class Statistics {
private:
  std::vector<std::array<double, 3>> _objectives;
  std::map<std::string, std::array<int, 4>> _optUsageMap;
  std::vector<std::map<std::string, std::array<int, 4>>> _optIterationUsageMap;

public:
  void collectObjective(double current, double candidate, double best);
  void initOptCounts(const std::string& optString);
  void addOptCounts(const std::string& optString, int weight_idx);
  void updateOptUsageMap();
  void printOptUsage();
  void saveObjective(const std::string& save_path);
  void saveOptUsage(const std::string& save_path);
};

} // namespace alns

#endif // ALNS_STATISTICS_H
