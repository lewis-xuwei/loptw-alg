#ifndef __ALNS_INCLUDE_TSP_POINT_H__
#define __ALNS_INCLUDE_TSP_POINT_H__

#include <iostream>

class Point {
  friend std::ostream& operator<<(std::ostream& out, const Point& point);

public:
  Point(int id, double x, double y);
  ~Point();

  double GetDistance(const Point& point);

public:
  int id_;
  double x_;
  double y_;
};

std::ostream& operator<<(std::ostream& out, const Point& point);

#endif // __ALNS_INCLUDE_TSP_POINT_H__
