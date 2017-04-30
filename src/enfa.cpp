#include "enfa.h"

#include <queue>
#include <set>
#include <string>
#include <vector>

#include "parser.h"
#include "resyntax/RegExp.h"

namespace tinygrep {

namespace enfa {

EpsilonNFA::EpsilonNFA(resyntax::RegExp re) {
  state_count_ = 0;
  StatePair sp = make_enfa(re);
  start_state_ = sp.start;
  accept_state_ = sp.accept;
}

EpsilonNFA::EpsilonNFA(std::string re) : EpsilonNFA::EpsilonNFA(parse(re)) {}

EpsilonNFA::StatePair EpsilonNFA::make_enfa(const resyntax::RegExp& re) {
  state_type new_start = increment_state(), new_accept = increment_state();
  switch(re.getType()) {
    case resyntax::RegExpEnum::kEmpty:
    { // accept anything
      epsilon_transitions_[new_start].push_back(new_accept);
      break;
    }
    case resyntax::RegExpEnum::kLiteral:
    case resyntax::RegExpEnum::kDot:
    { // literal transition from start to end
      Transition t;
      t.target = new_accept;
      t.literal = re.getLiteral();
      if (re.getType() == resyntax::RegExpEnum::kDot) {
        t.literal = '.';
      }
      literal_transitions_[new_start].push_back(t);
      break;
    }
    case resyntax::RegExpEnum::kOneOrMore:
    case resyntax::RegExpEnum::kZeroOrOne:
    case resyntax::RegExpEnum::kClosure:
    { // loop back and loop forward transitions
      StatePair sp = make_enfa(re.getR1());
      epsilon_transitions_[new_start].push_back(sp.start);
      epsilon_transitions_[sp.accept].push_back(new_accept);
      // OneOrMore and Closure allows repeated occurrences.
      if (re.getType() != resyntax::RegExpEnum::kZeroOrOne) {
        epsilon_transitions_[new_accept].push_back(new_start);
      }
      // ZeroOrOne and Closure allows zero occurrences.
      if (re.getType() != resyntax::RegExpEnum::kOneOrMore) {
        epsilon_transitions_[new_start].push_back(new_accept);
      }
      break;
    }
    case resyntax::RegExpEnum::kConcatenation:
    { // serial chain sub-automata
      StatePair sp1 = make_enfa(re.getR1());
      StatePair sp2 = make_enfa(re.getR2());
      epsilon_transitions_[new_start].push_back(sp1.start);
      epsilon_transitions_[sp1.accept].push_back(sp2.start);
      epsilon_transitions_[sp2.accept].push_back(new_accept);
      break;
    }
    case resyntax::RegExpEnum::kUnion:
    { // parallel chain sub-automata
      StatePair sp1 = make_enfa(re.getR1());
      StatePair sp2 = make_enfa(re.getR2());
      epsilon_transitions_[new_start].push_back(sp1.start);
      epsilon_transitions_[new_start].push_back(sp2.start);
      epsilon_transitions_[sp1.accept].push_back(new_accept);
      epsilon_transitions_[sp2.accept].push_back(new_accept);
      break;
    }
    default:
      ; // Unreachable code.
  }
  return StatePair(new_start, new_accept);
}

EpsilonNFA::state_type EpsilonNFA::increment_state() {
  epsilon_transitions_.push_back(std::vector<state_type>());
  literal_transitions_.push_back(std::vector<Transition>());
  return state_count_++;
}

std::set<EpsilonNFA::state_type> epsilon_closure(const std::set<EpsilonNFA::state_type>& states, const std::vector<std::vector<EpsilonNFA::state_type>>& transitions) {
  std::queue<EpsilonNFA::state_type> to_visit;
  for (EpsilonNFA::state_type state : states) {
    to_visit.push(state);
  }
  std::set<EpsilonNFA::state_type> visited;
  while (!to_visit.empty()) {
    EpsilonNFA::state_type current = to_visit.front();
    to_visit.pop();
    if (visited.find(current) != visited.end())
      continue;
    visited.insert(current);
    for (EpsilonNFA::state_type next : transitions[current]) {
      to_visit.push(next);
    }
  }
  return visited;
}

bool EpsilonNFA::accepts(const std::string& s) const {
  std::set<state_type> current_states = epsilon_closure(std::set<state_type>{start_state_}, epsilon_transitions_);
  for (char current_literal : s) {
    std::set<state_type> next_states;
    // for each current state
    // get whatever states they reach through current_literal transitions
    for (state_type state : current_states) {
      for (Transition transition : literal_transitions_[state]) {
        if (transition.literal == current_literal || transition.literal == '.') {
          next_states.insert(transition.target);
        }
      }
    }
    current_states = epsilon_closure(next_states, epsilon_transitions_);
  }
  return current_states.find(accept_state_) != current_states.end();
}

}  // namespace enfa

}  // namespace tinygrep
