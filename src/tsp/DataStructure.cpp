#include <fstream>
#include <sstream>

#include <tsp/DataStructure.h>

DataStructure::DataStructure(const std::string& instance_file) :
  instance_file_(instance_file) {}

// 加载tsp算例
void DataStructure::Init() {
  std::cout << "Data Init..." << std::endl;
  std::cout << "Data Loading..." << std::endl;

  LoadInstance();

  int num_of_points = GetNumOfPoints();
  dist_matrix_
    = std::vector<std::vector<double>>(num_of_points,
                                       std::vector<double>(num_of_points, 0));

  for (int from = 0; from < num_of_points; from++) {
    for (int to = 0; to < num_of_points; to++) {
      dist_matrix_[from][to] = points_[from].GetDistance(points_[to]);
    }
  }
}

double DataStructure::GetDistance(int pi, int pj) const {
  return dist_matrix_[pi][pj];
}

size_t DataStructure::GetNumOfPoints() const {
  return points_.size();
}

const Point& DataStructure::GetPoint(int i) const {
  return points_.at(i);
}

void DataStructure::skip_line(std::ifstream& in_file, int line) {
  for (int i = 0; i < line; i++) {
    std::string line;
    std::getline(in_file, line);
  }
}

// 加载tsp算例
void DataStructure::LoadInstance() {
  int num_of_points = -1;

  std::ifstream in_file(instance_file_, std::ios::in);
  if (!in_file.is_open()) {
    throw std::runtime_error("File is not opened");
  }

  skip_line(in_file, 5);
  std::string line;
  std::getline(in_file, line);
  line = line.substr(line.find(':') + 1);

  num_of_points = std::stoi(line);

  points_.reserve(num_of_points);
  skip_line(in_file, 2);
  for (int i = 0; i < num_of_points; i++) {
    std::getline(in_file, line);
    std::istringstream istr(line);

    int id;
    double x;
    double y;

    istr >> id >> x >> y;
    points_.push_back({id, x, y});
  }
}
