#include "parser.h"

#include <string>

#include "resyntax/resyntax.h"

namespace tinygrep {

resyntax::RegExp parse(std::string s) {
  // TODO: for realz
  resyntax::RegExp a = resyntax::createLiteral('a');
  resyntax::RegExp b = resyntax::createLiteral('b');
  resyntax::RegExp c = resyntax::createLiteral('c');
  resyntax::RegExp a_or_b = resyntax::createUnion(a, b);
  resyntax::RegExp a_or_b_star = resyntax::createClosure(a_or_b);
  resyntax::RegExp tree = resyntax::createConcatenation(a_or_b_star, c);
  return tree;
}

}
