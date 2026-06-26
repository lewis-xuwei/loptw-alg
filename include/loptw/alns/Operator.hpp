
#ifndef __ALNS_INCLUDE_ALGORITHM_OPERATOR_HPP__
#define __ALNS_INCLUDE_ALGORITHM_OPERATOR_HPP__

#include <loptw/alns/RandomState.h>
#include <loptw/alns/headers.h>

template <class STATE_CLS>
class Operator {
private:
  std::string name;
  std::unordered_map<std::string, double> kwargs;
  STATE_CLS(*OptPtr)
  (const STATE_CLS& state, RandomState& _rnd_state);

public:
  std::string getName() {
    return name;
  };
  void setName(std::string name_) {
    name = std::move(name_);
  };
  void setOptPtr(STATE_CLS (*OptPtr_)(const STATE_CLS& state,
                                      RandomState& _rnd_state)) {
    OptPtr = OptPtr_;
  };
  STATE_CLS exec(const STATE_CLS& state, RandomState& _rnd_state) {
    return (*OptPtr)(state, _rnd_state);
  };
  Operator(STATE_CLS (*OptPtr_)(const STATE_CLS& state,
                                RandomState& _rnd_state)) {
    setOptPtr(OptPtr_);
  };
};

template <class STATE_CLS>
class Operators {
private:
  std::map<std::string, Operator<STATE_CLS>*> opt_ptr_map;
  std::map<int, std::string> opt_name_map;
  int size = 0;

public:
  int getSize() {
    return size;
  };

  void addOperator(Operator<STATE_CLS>* _operator, std::string& name) {
    if (name.length() == 0) {
      name = _operator->getName();
    } else {
      _operator->setName(name);
    }
    if (opt_ptr_map.count(name)) {
      std::cout << "The ALNS instance already knows an operator by the"
                   " name `{0}'. This operator will now be replaced with"
                   " the newly passed-in operator. If this is not what"
                   " you intended, consider explicitly naming your"
                   " operators via the `name' argument."
                << std::endl;
    } else {
      opt_name_map[size] = name;
      opt_ptr_map[name] = _operator;
      size += 1;
    }
  }

  Operator<STATE_CLS>* operator[](const std::string& key) {
    return opt_ptr_map[key];
  };
  Operator<STATE_CLS>* operator[](int idx) {
    return opt_ptr_map[opt_name_map[idx]];
  };
};

#endif // __ALNS_INCLUDE_ALGORITHM_OPERATOR_HPP__
