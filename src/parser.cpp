#include "parser.h"

#include <string>

#include "resyntax/resyntax.h"

namespace tinygrep {

resyntax::RegExp parse(std::string s) {
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

}
