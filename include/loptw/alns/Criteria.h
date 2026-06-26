
#ifndef __ALNS_INCLUDE_ALGORITHM_CRITERIA_H__
#define __ALNS_INCLUDE_ALGORITHM_CRITERIA_H__

#include <loptw/alns/RandomState.h>
#include <loptw/alns/headers.h>

namespace loptw::alns::Criterion {

enum UPDATE_METHOD { linear = 0, exponential = 1 };

class SimulatedAnnealing {
private:
  double _start_temp;
  double _end_temp;
  double _step;
  double _temp;
  UPDATE_METHOD _method;

public:
  SimulatedAnnealing(double start_temp,
                     double end_temp,
                     double step,
                     UPDATE_METHOD method = linear);

  bool accept(RandomState& randomState,
              double best,
              double current,
              double candidate);

  static double update(double current, double step, UPDATE_METHOD method);
};

} // namespace loptw::alns::Criterion

#endif // __ALNS_INCLUDE_ALGORITHM_CRITERIA_H__
