

#include <tsp/State.h>

#include <algorithm>
#include <chrono>

namespace tsp {

double State::Objective() const {
  size_t num_of_nodes = nodes_list_.size();

  std::set<int> node_set(nodes_list_.begin(), nodes_list_.end());
  if (node_set.size() != num_of_nodes)
    return std::numeric_limits<double>::infinity();

  double obj = data_structure_->GetDistance(nodes_list_[0],
                                            nodes_list_[num_of_nodes - 1]);

  for (size_t i = 0; i < num_of_nodes - 1; i++) {
    int from = nodes_list_[i];
    int to = nodes_list_[i + 1];
    obj += data_structure_->GetDistance(from, to);
  }

  return obj;
}

State State::Init(DataStructure* data_structure,
                  double degree_of_destruction,
                  alns::RandomState& rand_state) {
  State state;
  state.degree_of_destruction_ = degree_of_destruction;
  state.data_structure_ = data_structure;

  size_t num_of_points{data_structure->GetNumOfPoints()};
  std::vector<int> node_list;
  node_list.reserve(num_of_points);

  for (int i = 0; i < num_of_points; i++) {
    node_list.push_back(i);
  }

  rand_state.shuffle(node_list);
  state.nodes_list_ = node_list;
  return std::move(state);
}

void State::PrintResult() const {
  std::cout << "[";
  for (auto node : nodes_list_) {
    std::cout << node << " ";
  }
  std::cout << "]" << std::endl;

  if (!uninserted_nodes_list_.empty()) {
    std::cout << "[";
    for (auto node : uninserted_nodes_list_) {
      std::cout << node << " ";
    }
    std::cout << "]" << std::endl;
  }
}

State State::RandomRemoval(const State& state, alns::RandomState& rnd_state) {
  size_t num_points = state.data_structure_->GetNumOfPoints();
  size_t num_removed = state.degree_of_destruction_ * num_points;

  State destroyed(state);

  for (size_t i = 0; i < num_removed; i++) {
    int size = destroyed.nodes_list_.size();

    int index = rnd_state.sample_idx(size);
    int node = destroyed.nodes_list_[index];
    auto pos = destroyed.nodes_list_.begin() + index;

    destroyed.uninserted_nodes_list_.push_back(node);
    destroyed.nodes_list_.erase(pos);
  }

  return destroyed;
}

State State::GreedyInsertion(const State& state, alns::RandomState& rnd_state) {
  State repaired(state);
  repaired.PrintResult();

  for (auto node : repaired.uninserted_nodes_list_) {
    double min_obj = std::numeric_limits<double>::infinity();
    double index = -1;
    double cur_obj = repaired.Objective();

    int size = repaired.nodes_list_.size();
    for (int i = 0; i < size; i++) {
      int from = repaired.nodes_list_[i];
      int to = repaired.nodes_list_[i == 0 ? size - 1 : i];

      double new_obj = cur_obj - state.data_structure_->GetDistance(from, to)
                       + state.data_structure_->GetDistance(from, node)
                       + state.data_structure_->GetDistance(node, to);

      if (new_obj < min_obj) {
        min_obj = new_obj;
        index = i;
      }
    }
    auto pos = repaired.nodes_list_.begin() + index;
    repaired.nodes_list_.insert(pos, node);
  }

  repaired.uninserted_nodes_list_.clear();

  return repaired;
}

} // namespace tsp