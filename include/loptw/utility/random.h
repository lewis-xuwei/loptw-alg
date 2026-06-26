///======================================================
/// Project :   loptw-bnc
/// File    :   random.h
///------------------------------------------------------
/// Time    :   2026/06/01 17:46:17
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_RANDOM_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_RANDOM_H__

#include <random>
#include <vector>

namespace loptw::utility {

class Random {
private:
  static inline int seed_ = -1;
  static inline std::random_device rd_;
  static inline std::mt19937 gen_{rd_()};

public:
  static void SetSeed(int seed = -1);

  /// @brief return a random double in [min, max)
  static double Uniform(double min = 0.0, double max = 1.0);

  /// @brief return a random integer in [min, max]
  static int Uniform(int min, int max);

  /// @brief return a random index in [0, size)
  static int Index(unsigned size);

  /// @brief shuffle a vector of integers
  static void Shuffle(std::vector<int>& vec);
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_RANDOM_H__
