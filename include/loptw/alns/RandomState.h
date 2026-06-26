
#ifndef ALNS_RANDOMSTATE_H
#define ALNS_RANDOMSTATE_H

#include <loptw/alns/headers.h>

class RandomState {
private:
  int _seed = 0;
  std::random_device _rd;

public:
  explicit RandomState(int init_seed);

  double uniform(double min, double max);

  int sample_idx(unsigned size);

  int sample_idx_with_exp_prob(int size, double p);

  std::vector<unsigned> sample_idxes_in_range(const unsigned& size,
                                              double ratio_lb,
                                              double ratio_ub);
};
#endif // ALNS_RANDOMSTATE_H
