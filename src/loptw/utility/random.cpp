///======================================================
/// Project :   loptw-bnc
/// File    :   random.cpp
///------------------------------------------------------
/// Time    :   2026/06/01 18:29:33
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <algorithm>

#include <loptw/utility/random.h>

namespace loptw::utility {

void Random::SetSeed(int seed) {
  seed_ = seed == -1 ? rd_() : seed;
  gen_.seed(seed_);
}

/// @brief return a random double in [min, max)
double Random::Uniform(double min, double max) {
  std::uniform_real_distribution<double> dis(min, max);
  return dis(Random::gen_);
}

/// @brief return a random integer in [min, max]
int Random::Uniform(int min, int max) {
  std::uniform_int_distribution<int> dis(min, max);
  return dis(Random::gen_);
}

/// @brief return a random index in [0, size)
int Random::Index(unsigned size) {
  std::uniform_int_distribution<int> dis(0, size - 1);
  return dis(Random::gen_);
}

/// @brief shuffle a vector of integers
void Random::Shuffle(std::vector<int>& vec) {
  std::shuffle(vec.begin(), vec.end(), Random::gen_);
}

std::vector<int> Random::RandomPermutation(int n, int start) {
  std::vector<int> perm;
  perm.reserve(n);
  for (int i = 0; i < n; ++i) {
    perm.push_back(start + i);
  }
  Random::Shuffle(perm);
  return std::move(perm);
}

} // namespace loptw::utility