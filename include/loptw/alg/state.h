///======================================================
/// Project :   loptw-alg
/// File    :   state.h
///------------------------------------------------------
/// Time    :   2026/06/28 11:13:02
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <alns/RandomState.h>

namespace loptw::alg {

class State {
public:
  // Calculate the objective
  double Objective() const;

  // Print the result
  void PrintResult() const;

  static State RandomRemoval(const State& state, alns::RandomState& rnd_state);
  static State BestRepair(const State& state, alns::RandomState& rnd_state);

private:
};

} // namespace loptw::alg
