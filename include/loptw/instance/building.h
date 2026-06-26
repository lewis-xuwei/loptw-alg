///======================================================
/// Project :   loptw-bnc
/// File    :   building.h
///------------------------------------------------------
/// Time    :   2026/04/23 20:25:59
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_BUILDING_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_BUILDING_H__

#include <loptw/instance/types.h>

namespace loptw::instance {

class Building {
public:
  using Key = Index;

public:
  Building() = delete;
  Building(Index building_id,
           double left_coord,
           double bottom_coord,
           double width,
           double length,
           double rent_cost);

  /// @brief Check whether overlap with other
  /// @param other
  /// @return true if this overlap with other, otherwise false
  bool OverlapWith(const Building& other) const;

public:
  Index building_id_;
  double left_coord_;
  double bottom_coord_;
  double width_;
  double length_;
  double right_coord_;
  double top_coord_;
  double rent_cost_;
};

} // namespace loptw::instance

#endif // __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_BUILDING_H__
