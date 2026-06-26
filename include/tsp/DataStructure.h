#ifndef __ALNS_INCLUDE_TSP_DATASTRUCTURE_H__
#define __ALNS_INCLUDE_TSP_DATASTRUCTURE_H__

#include <tsp/Point.h>

#include <string>
#include <vector>

// 定义 TSP 问题结构
class DataStructure {
  friend std::ostream& operator<<(std::ostream& out,
                                  const DataStructure& data_structure);

public:
  DataStructure(const std::string& instance_file);

  void Init();
  size_t GetNumOfPoints() const;
  double GetDistance(int pi, int pj) const;
  const Point& GetPoint(int i) const;

private:
  void LoadInstance();
  static void skip_line(std::ifstream& in_file, int line = 1);

private:
  std::vector<std::vector<double>> dist_matrix_;

private:
  std::string instance_file_;
  std::vector<Point> points_;
};

std::ostream& operator<<(std::ostream& out,
                         const DataStructure& data_structure);

#endif // __ALNS_INCLUDE_TSP_DATASTRUCTURE_H__
