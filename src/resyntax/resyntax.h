#ifndef TINYGREP_RESYNTAX_RESYNTAX_
#define TINYGREP_RESYNTAX_RESYNTAX_

#include "graph.h"
#include "RegExp.h"

namespace tinygrep {

namespace resyntax {

RegExp createClosure(RegExp r);
RegExp createConcatenation(RegExp r1, RegExp r2);
RegExp createDot();
RegExp createLiteral(RegExp::literalType literal);
RegExp createOneOrMore(RegExp r);
RegExp createUnion(RegExp r1, RegExp r2);
RegExp createZeroOrOne(RegExp r);

}  // namespace resyntax

}  // namespace tinygrep

#endif // TINYGREP_RESYNTAX_RESYNTAX_
