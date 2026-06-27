
#include <alns/RandomState.h>

namespace alns {

double RandomState::uniform(double min, double max) {
  std::uniform_real_distribution<double> dist(min, max);
  return dist(_mt);
}

RandomState::RandomState(int init_seed) {
  _seed = init_seed;
  if (_seed == -1)
    _mt.seed(_rd());
  else
    _mt.seed(_seed);
}

int RandomState::sample_idx(unsigned int size) {
  std::uniform_int_distribution<int> dis(0, size - 1);
  return dis(_mt);
}

int RandomState::sample_idx_with_exp_prob(int size, double p) {
  if (p < 0) {
    return 0;
  }

  int num_intervals = size / 2;
  std::vector<double> intervals(num_intervals);
  std::vector<double> weights(num_intervals);
  for (int i = 0; i < num_intervals; i++) {
    int val = size / num_intervals * i;
    intervals.push_back(val);
    weights.push_back(std::exp(-p * val));
  }
  intervals.push_back(size);
  weights.push_back(std::exp(-p * size));

  std::piecewise_linear_distribution<> dist(intervals.begin(),
                                            intervals.end(),
                                            weights.begin());
  return dist(_mt);
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
  int sample_num = (int)(uniform(ratio_lb, ratio_ub) * size);
  std::vector<unsigned> idxes;
  idxes.reserve(sample_num);
  for (int i = 0; i < sample_num; ++i) {
    int removeIdx = sample_idx(iterable_.size());
    auto removeItr = std::next(iterable_.begin(), removeIdx);
    idxes.push_back(*removeItr);
    iterable_.erase(removeItr);
  }

  return idxes;
};

} // namespace alns