#include "enfa.h"

#include <string>
#include <sstream>

namespace tinygrep {

namespace enfa {

// The default scale of a generated graph.
const unsigned int DEFAULT_PNG_SIZE = 10;
const std::string LABEL_BEGIN   = " [label=\"",
                  LABEL_END     = "\"]",
                  EDGE_ARROW    = " -> ",
                  STATE_PREFIX  = "q",
                  ENDLINE       = ";\n";

std::string EpsilonNFA::to_graph() const {
  const unsigned int png_size = DEFAULT_PNG_SIZE;
  std::stringstream output;
  output << "digraph epsilon_nfa {\n"
         << "rankdir=LR; size=\""
         << png_size << "," << png_size << "\""
         << ENDLINE;
  // add start state
  output << "foo [style = invis]"
         << ENDLINE;
  output << "node [shape = circle]; "
         << STATE_PREFIX << start_state_
         << ENDLINE;
  output << "foo" << EDGE_ARROW
         << STATE_PREFIX << start_state_
         << LABEL_BEGIN << "start" << LABEL_END
         << ENDLINE;
  // add accepting state
  output << "node [shape = doublecircle]; "
         << STATE_PREFIX << accept_state_
         << ENDLINE;
  // add remaining states
  output << "node [shape = circle]"
         << ENDLINE;
  // add transitions
  for (state_type from = 0; from < state_count_; from++) {
    // epsilon-transitions
    for (state_type to : epsilon_transitions_[from]) {
      output << STATE_PREFIX << from
             << EDGE_ARROW
             << STATE_PREFIX << to
             << LABEL_BEGIN << LABEL_END
             << ENDLINE;
    }
    // literal-transitions
    for (Transition transition : literal_transitions_[from]) {
      output << STATE_PREFIX << from
             << EDGE_ARROW
             << STATE_PREFIX << transition.target
             << LABEL_BEGIN << transition.literal << LABEL_END
             << ENDLINE;
    }
  }
  output << "}\n";
  return output.str();
}

}  // namespace enfa

}  // namespace tinygrep
