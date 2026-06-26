
#include <loptw/alns/Criteria.h>

namespace loptw::alns {

Criterion::SimulatedAnnealing::SimulatedAnnealing(double start_temp,
                                                  double end_temp,
                                                  double step,
                                                  UPDATE_METHOD method) {
  _start_temp = start_temp;
  _end_temp = end_temp;
  _step = step;
  _method = method;
  _temp = _start_temp;
}

bool Criterion::SimulatedAnnealing::accept(RandomState& randomState,
                                           double best,
                                           double current,
                                           double candidate) {
  double prob = std::min(std::exp((current - candidate) / _temp), 1.);
  prob = std::max(0.0001, prob);
  std::cout << "Accept Prob=" << prob * 100 << "%; ";
  _temp = std::max(_end_temp, update(_temp, _step, _method));
  bool accepted = prob > randomState.uniform(0., 1.);
  return accepted;
}

double Criterion::SimulatedAnnealing::update(double current,
                                             double step,
                                             UPDATE_METHOD method) {
  switch (method) {
  case linear:
    return current - step;
  case exponential:
    return current * step;
  }
  return 0.;
}

} // namespace loptw::alns