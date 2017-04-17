#ifndef TINYGREP_RESYNTAX_RESYNTAX_
#define TINYGREP_RESYNTAX_RESYNTAX_

#include "RegExp.h"

namespace resyntax {

RegExp createClosure(RegExp r);
RegExp createConcatenation(RegExp r1, RegExp r2);
RegExp createDot();
RegExp createLiteral(RegExp::literalType literal);
RegExp createOneOrMore(RegExp r);
RegExp createUnion(RegExp r1, RegExp r2);
RegExp createZeroOrOne(RegExp r);

}

#endif //  TINYGREP_RESYNTAX_RESYNTAX_
