#include <tsp/Point.h>

#include <cmath>

std::ostream& operator<<(std::ostream& out, const Point& point) {
  out << "Point<" << point.id_ << ">: {x = " << point.x_ << ", y = " << point.y_
      << "}" << std::endl;
  return out;
}

Point::Point(int id, double x, double y) : id_(id), x_(x), y_(y) {}

Point::~Point() {}

double Point::GetDistance(const Point& point) {
  return std::sqrt((point.x_ - x_) * (point.x_ - x_)
                   + (point.y_ - y_) * (point.y_ - y_));
}
