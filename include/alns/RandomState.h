
#ifndef ALNS_RANDOMSTATE_H
#define ALNS_RANDOMSTATE_H

#include <alns/headers.h>

namespace alns {

class RandomState {
private:
  int _seed = -1;
  std::random_device _rd;
  std::mt19937 _mt;

public:
  explicit RandomState(int init_seed = -1);

  double uniform(double min, double max);

  int sample_idx(unsigned size);

  int sample_idx_with_exp_prob(int size, double p);

  std::vector<unsigned> sample_idxes_in_range(const unsigned& size,
                                              double ratio_lb,
                                              double ratio_ub);
  template <class T>
  void shuffle(std::vector<T>& vec) {
    std::shuffle(vec.begin(), vec.end(), _mt);
  }
};

} // namespace alns

#endif // ALNS_RANDOMSTATE_H
