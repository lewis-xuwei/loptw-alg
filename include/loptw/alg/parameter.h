///======================================================
/// Project :   loptw-alg
/// File    :   parameter.h
///------------------------------------------------------
/// Time    :   2026/07/04 16:21:11
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_ALG_PARAMETER_H__
#define __LOPTW_ALG_INCLUDE_LOPTW_ALG_PARAMETER_H__

namespace loptw::alg {

// Parameter struct for tabu search algorithm
struct Parameter {
  int max_iters;                // maximum number of iterations
  int max_nonimp;               // maximum number of non-improvement
  int num_cand;                 // number of candidate
  int num_tenure;               // the number of iterations when is put into tabu list
  double initial_temperature;   // initial temperature for simulated annealing
  double cooling_rate;          // cooling rate for simulated annealing
  double decay_rate;            // decay rate for adaptive weight adjustment
  double weight_best;           // weight for the best solution
  double weight_better;         // weight for better solutions
  double weight_accepted;       // weight for accepted moves
  double weight_rejected;       // weight for rejected moves
  double degree_of_destruction; // degree of destruction for random removal
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_PARAMETER_H__
