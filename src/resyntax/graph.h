#ifndef TINYGREP_RESYNTAX_GRAPH_
#define TINYGREP_RESYNTAX_GRAPH_

#include <sstream>
#include <string>

#include "RegExp.h"

namespace tinygrep {

namespace resyntax {

// The default scale of a generated graph.
const unsigned int DEFAULT_PNG_SIZE = 10;

// Returns a string containing the regexp visualized in the graphviz .gv format, readable with <dot> command.
std::string to_graph(const RegExp& re, const unsigned int png_size = DEFAULT_PNG_SIZE);

unsigned int generate_node_strings(const RegExp& re, std::stringstream& nodes, std::stringstream& edges, unsigned int node_id = 0);

}  // namespace resyntax

}  // namespace tinygrep

#endif // TINYGREP_RESYNTAX_GRAPH_
