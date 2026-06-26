///======================================================
/// Project :   loptw-bnc
/// File    :   building.cpp
///------------------------------------------------------
/// Time    :   2026/04/24 11:31:55
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/instance/building.h>

namespace loptw::instance {

Building::Building(Index building_id, double left_coord, double bottom_coord,
                   double width, double length, double rent_cost)
    : building_id_{building_id}, left_coord_{left_coord},
      bottom_coord_{bottom_coord}, width_{width}, length_{length},
      rent_cost_{rent_cost} {
  right_coord_ = left_coord_ + width_;
  top_coord_ = bottom_coord_ + length_;
}

bool Building::OverlapWith(const Building &other) const {
  // other in left
  if (other.right_coord_ <= left_coord_)
    return false;

  // other in bottom
  if (other.top_coord_ <= bottom_coord_)
    return false;

  // other in right
  if (other.left_coord_ >= right_coord_)
    return false;

  // other in top
  if (other.bottom_coord_ >= top_coord_)
    return false;

  return true;
}

} // namespace loptw::instance
