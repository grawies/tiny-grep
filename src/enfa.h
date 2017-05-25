#ifndef TINYGREP_ENFA_H_
#define TINYGREP_ENFA_H_

#include <cstddef>
#include <string>
#include <vector>

#include "resyntax/RegExp.h"

namespace tinygrep {

namespace enfa {

class EpsilonNFA {
 public:
  typedef std::size_t state_type;
  
  explicit EpsilonNFA(const resyntax::RegExp& re);
  explicit EpsilonNFA(const std::string& re);

  bool accepts(const std::string& s) const;

  std::string to_graph() const;

 private:
  std::string alphabet_;
  std::size_t state_count_;
  state_type start_state_, accept_state_;
  struct Transition {
   state_type target;
   resyntax::RegExp::literalType literal;
  };
  std::vector<std::vector<state_type>> epsilon_transitions_;
  std::vector<std::vector<Transition>> literal_transitions_;
  struct StatePair {
    state_type start, accept;
    StatePair(state_type s, state_type a) : start(s), accept(a) {};
  };
  StatePair make_enfa(const resyntax::RegExp& re);
  state_type increment_state();
};

}  // namespace enfa

}  // namespace tinygrep

#endif // TINYGREP_ENFA_H_
