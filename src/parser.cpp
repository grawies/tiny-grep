#include "parser.h"

#include <cstddef>
#include <stdexcept>
#include <string>

#include "resyntax/resyntax.h"

namespace tinygrep {

// Find end of parenthesis subexpr in string:
// returns index s.t. [start_index, index) includes both parentheses.
std::size_t find_matching_parenthesis(const std::string& s, std::size_t start_index) {
  std::size_t index = start_index + 1;
  int unmatched_left_parens = 1;
  for (auto it = s.begin() + index; it < s.end() && unmatched_left_parens > 0; ++it, ++index) {
    if (*it == '(') {
      ++unmatched_left_parens;
    } else if (*it == ')') {
      --unmatched_left_parens;
    }
  }
  if (unmatched_left_parens != 0) {
    throw std::domain_error("String is not in the supported grammar: unmatched parenthesis.");
  }
  return index;
}

resyntax::RegExp parse(const std::string s) {
  // TODO: Validate s: check if it belongs to the grammar.
  // TODO: Implement the parsing function based on the pseudocode.

  //  init UNION-list
  //  init CONCAT-list
  //  while charstream is nonempty:
  //    c <- next char
  //    if c == ( :
  //      subexpr <- find subexpr
  //      CONCAT.append: recurse(subexpr)
  //    if c == . :
  //      CONCAT.append: DOT
  //    if c == literal :
  //      CONCAT.append: LITERAL(c)
  //    if c in {+,?,*} :
  //      CONCAT.top.modifywith(c)
  //    if c == | :
  //      cct <- CONCAT.CONCATENATEALL
  //      UNION.append: cct
  //      init CONCAT-list anew
  //    else
  //      throw a_fit
  //  cct <- CONCAT.CONCATENATEALL
  //  UNION.append: cct
  //  regexp <- UNION.UNITEALL
  //  return regexp

  // This is a temporary placeholder construction for verifying that testing is functional.
  resyntax::RegExp a = resyntax::createLiteral('a');
  resyntax::RegExp b = resyntax::createLiteral('b');
  resyntax::RegExp c = resyntax::createLiteral('c');
  resyntax::RegExp a_or_b = resyntax::createUnion(a, b);
  resyntax::RegExp a_or_b_star = resyntax::createClosure(a_or_b);
  resyntax::RegExp tree = resyntax::createConcatenation(a_or_b_star, c);
  return tree;
}

}  // namespace tinygrep
