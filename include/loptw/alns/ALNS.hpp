#ifndef __ALNS_INCLUDE_ALGORITHM_ALNS_HPP__
#define __ALNS_INCLUDE_ALGORITHM_ALNS_HPP__

#include <loptw/alns/Criteria.h>
#include <loptw/alns/Operator.hpp>
#include <loptw/alns/RandomState.h>
#include <loptw/alns/Statistics.h>
#include <loptw/alns/headers.h>

namespace loptw::alns {

enum ITERATE_STATE {
  IS_BEST = 0,
  IS_BETTER = 1,
  IS_ACCEPTED = 2,
  IS_REJECTED = 3,
};

template <class STATE_CLS, class CRITERIA_CLS>
class ALNS {
private:
  Statistics _statistics = Statistics();
  Operators<STATE_CLS> _destroy_operators_ptr;
  Operators<STATE_CLS> _repair_operators_ptr;
  RandomState* _rnd_state;

public:
  explicit ALNS(RandomState* rnd_state) {
    _rnd_state = rnd_state;
  };
  void add_destroy_operator(Operator<STATE_CLS>* opt,
                            std::string opt_name = "") {
    _destroy_operators_ptr.addOperator(opt, opt_name);
    _statistics.initOptCounts(opt_name);
  };
  void add_repair_operator(Operator<STATE_CLS>* opt,
                           std::string opt_name = "") {
    _repair_operators_ptr.addOperator(opt, opt_name);
    _statistics.initOptCounts(opt_name);
  };
  STATE_CLS iterate(STATE_CLS initial_solution,
                    std::array<double, 4> adaptive_weight_change,
                    double operator_decay,
                    CRITERIA_CLS criterion,
                    int iterations,
                    bool collect_stats,
                    const std::string& objective_path,
                    const std::string& opt_usage_path) {
    // validate_parameters
    _statistics.updateOptUsageMap();

    // copy initial solution to current & best
    STATE_CLS current{initial_solution};
    STATE_CLS best{initial_solution};

    // initial opt weight
    std::vector<double> d_weights;
    d_weights.reserve(_destroy_operators_ptr.getSize());
    for (int i = 0; i < _destroy_operators_ptr.getSize(); ++i) {
      d_weights.push_back(1);
    }
    std::vector<double> r_weights;
    r_weights.reserve(_repair_operators_ptr.getSize());
    for (int i = 0; i < _repair_operators_ptr.getSize(); ++i) {
      r_weights.push_back(1);
    }
    if (collect_stats) {
      _statistics.collectObjective(initial_solution.Objective(),
                                   initial_solution.Objective(),
                                   initial_solution.Objective());
    }
    std::cout.precision(4);
    for (int iteration = 1; iteration < iterations + 1; ++iteration) {
      int d_idx = _select_operator_idx(d_weights);
      int r_idx = _select_operator_idx(r_weights);

      STATE_CLS destroyed
        = _destroy_operators_ptr[d_idx]->exec(current, *_rnd_state);
      STATE_CLS candidate
        = _repair_operators_ptr[r_idx]->exec(destroyed, *_rnd_state);

      int weightChangeIndex
        = _consider_candidate_weight_idx(best, current, candidate, criterion);

      // refresh opt weights
      d_weights[d_idx] *= operator_decay;
      d_weights[d_idx]
        += (1 - operator_decay) * adaptive_weight_change[weightChangeIndex];

      r_weights[r_idx] *= operator_decay;
      r_weights[r_idx]
        += (1 - operator_decay) * adaptive_weight_change[weightChangeIndex];

      if (collect_stats) {
        _statistics.collectObjective(current.Objective(),
                                     candidate.Objective(),
                                     best.Objective());
        _statistics.addOptCounts(_destroy_operators_ptr[d_idx]->getName(),
                                 weightChangeIndex);
        _statistics.addOptCounts(_repair_operators_ptr[r_idx]->getName(),
                                 weightChangeIndex);
        _statistics.updateOptUsageMap();
      }

      std::cout << "\r" << iteration << "/" << iterations << " | "
                << "Current=" << current.Objective()
                << "; Candidate=" << candidate.Objective()
                << "; Best=" << best.Objective() << " | ";
      _statistics.printOptUsage();
      std::cout << "DestroyOptWeights=[";
      for (unsigned i = 0; i < d_weights.size(); ++i) {
        std::cout << _destroy_operators_ptr[i]->getName() << "=" << d_weights[i]
                  << ";";
      }
      std::cout << "]; ";
      std::cout << "RepairOptWeights=[";
      for (unsigned i = 0; i < r_weights.size(); ++i) {
        std::cout << _repair_operators_ptr[i]->getName() << "=" << r_weights[i]
                  << ";";
      }
      std::cout << "]" << std::flush;

      if (weightChangeIndex == IS_BEST || iteration == 1) {
        best.PrintResult();
      }
    }
    if (collect_stats) {
      _statistics.saveObjective(objective_path);
      _statistics.saveOptUsage(opt_usage_path);
    }
    return best;
  };
  int _consider_candidate_weight_idx(STATE_CLS& best,
                                     STATE_CLS& current,
                                     STATE_CLS& candidate,
                                     CRITERIA_CLS& criterion) {
    int weight_idx;
    if (criterion.accept(*_rnd_state,
                         best.Objective(),
                         current.Objective(),
                         candidate.Objective())) {
      if (candidate.Objective() < current.Objective()) {
        weight_idx = IS_BETTER;
      } else {
        weight_idx = IS_ACCEPTED;
      }
      current = candidate;
    } else {
      weight_idx = IS_REJECTED;
    }
    if (candidate.Objective() < best.Objective()) {
      best = candidate;
      weight_idx = IS_BEST;
    }
    return weight_idx;
  };
  int _select_operator_idx(const std::vector<double>& weights) const {
    double gamble_idx = _rnd_state->uniform(0.0,
                                            std::accumulate(weights.begin(),
                                                            weights.end(),
                                                            0.0));
    double curr_sum = 0.;
    int select_idx = 0;
    for (const auto& weight : weights) {
      curr_sum += weight;
      if (curr_sum > gamble_idx) {
        return select_idx;
      }
      select_idx += 1;
    }
    return 0;
  };
};

} // namespace loptw::alns

#endif // __ALNS_INCLUDE_ALGORITHM_ALNS_HPP__
