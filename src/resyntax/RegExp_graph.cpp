#include "RegExp.h"

#include <cstddef>
#include <sstream>
#include <string>

namespace tinygrep {

namespace resyntax {

const unsigned int DEFAULT_PNG_SIZE = 10;
const std::string LABEL_BEGIN = " [label=\"",
                  LABEL_END   = "\"]",
                  EDGE_ARROW  = " -> ",
                  ENDLINE     = ";\n";

std::string to_string(const RegExp& re) {
  switch (re.getType()) {
    case RegExpEnum::kEmpty:
      return "$\\epsilon$";
    case RegExpEnum::kLiteral:
      return re.getLiteral().to_string();
    case RegExpEnum::kDot:
      return "dot";
    case RegExpEnum::kOneOrMore:
      return "+";
    case RegExpEnum::kZeroOrOne:
      return "?";
    case RegExpEnum::kClosure:
      return "*";
    case RegExpEnum::kConcatenation:
      return "&";
    case RegExpEnum::kUnion:
      return "|";
    default:
      return "N/A";
  }
}

unsigned int generate_node_strings(const RegExp& re, std::stringstream& nodes, std::stringstream& edges, unsigned int node_id) {
  const unsigned int curr_node_id = node_id;
  nodes << curr_node_id << LABEL_BEGIN << to_string(re) << LABEL_END << ENDLINE;
  node_id++;

  switch (re.getType()) {
    case RegExpEnum::kEmpty:
    case RegExpEnum::kLiteral: 
    case RegExpEnum::kDot:
      break;
    case RegExpEnum::kOneOrMore:
    case RegExpEnum::kZeroOrOne:
    case RegExpEnum::kClosure:
      edges << curr_node_id << EDGE_ARROW << node_id << ENDLINE;
      node_id = generate_node_strings(re.getR1(), nodes, edges, node_id);
      break;
    case RegExpEnum::kConcatenation:
    case RegExpEnum::kUnion:
      edges << curr_node_id << EDGE_ARROW << node_id << ENDLINE;
      node_id = generate_node_strings(re.getR1(), nodes, edges, node_id);
      edges << curr_node_id << EDGE_ARROW << node_id << ENDLINE;
      node_id = generate_node_strings(re.getR2(), nodes, edges, node_id);
      break;
    default:
      nodes << "// < Omitted: unsupported node type. >\n";
      break;
  }
  return node_id;
}

std::string RegExp::to_graph() const {
  const unsigned int png_size = DEFAULT_PNG_SIZE;
  std::stringstream output;
  output << "digraph epsilon_nfa {\nrankdir=LR; size=\""
                << png_size << "," << png_size << "\";\n"
                << "node [shape = circle];\n";
  std::stringstream nodes, edges;
  generate_node_strings(*this, nodes, edges, 0);
  output << nodes.str() << edges.str() << "}\n";
  return output.str();
}

}  // namespace resyntax

}  // namespace tinygrep
