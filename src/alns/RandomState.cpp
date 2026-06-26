
#include <alns/RandomState.h>

namespace alns {

double RandomState::uniform(double min, double max) {
  std::uniform_real_distribution<double> dist(min, max);
  std::mt19937 mt(_seed);
  _seed = _rd();
  return dist(mt);
}

RandomState::RandomState(int init_seed) {
  _seed = init_seed;
}

int RandomState::sample_idx(unsigned int size) {
  return (int)((size - 1) * uniform(0., 1.));
}

int RandomState::sample_idx_with_exp_prob(int size, double p) {
  if (p <= 0) {
    return 0;
  }
  return (int)((size - 1) * std::pow(uniform(0., 1.), p));
}

std::vector<unsigned> RandomState::sample_idxes_in_range(
  const unsigned int& size,
  double ratio_lb,
  double ratio_ub) {
  if (size == 1) {
    return std::vector<unsigned>{0};
  }
  // copy iterable
  std::list<unsigned> iterable_;
  for (unsigned i = 0; i < size; ++i) {
    iterable_.push_back(i);
  }
  // do sample
  std::vector<unsigned> idxes;
  int sample_num = (int)(uniform(ratio_lb, ratio_ub) * size);
  for (int i = 0; i < sample_num; ++i) {
    int removeIdx = sample_idx(iterable_.size());
    auto removeItr = std::next(iterable_.begin(), removeIdx);
    idxes.push_back(*removeItr);
    iterable_.erase(removeItr);
  }
  return idxes;
};

} // namespace alns