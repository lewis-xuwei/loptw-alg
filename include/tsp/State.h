#ifndef __ALNS_INCLUDE_TSP_STATE_H__
#define __ALNS_INCLUDE_TSP_STATE_H__

#include <alns/RandomState.h>
#include <tsp/DataStructure.h>

namespace tsp {

// 定义TSP解结构
class State {
public:
  // Calculate the objective
  double Objective() const;

  // Print the result
  void PrintResult() const;

  // Initialization
  static State Init(DataStructure* data_structure,
                    double degree_of_destruction);

  // Removal
  static State RandomRemoval(const State& state, alns::RandomState& rnd_state);

  // Insertion
  static State GreedyInsertion(const State& state,
                               alns::RandomState& rnd_state);

private:
  template <class Tp>
  static const Tp& GetElemOfListByIndex(const std::list<Tp>& list,
                                        size_t index) {
    if (index >= 0 && index < list.size()) {
      auto iter = list.begin();
      for (size_t i = 0; i < index; i++) {
        iter++;
      }
      return *iter;
    }
    throw std::out_of_range("GetElemOfListByIndex");
  }

private:
  double degree_of_destruction_;
  DataStructure* data_structure_;

private:
  std::vector<int> nodes_list_;
  std::vector<int> uninserted_nodes_list_;
};

} // namespace tsp

#endif // __ALNS_INCLUDE_TSP_STATE_H__
