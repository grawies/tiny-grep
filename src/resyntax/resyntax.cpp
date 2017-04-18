#include "resyntax.h"

#include "RegExp.h"

namespace tinygrep {

namespace resyntax {

RegExp createClosure(RegExp r) {
  RegExp a(RegExpEnum::kClosure, r);
  return a;
}

RegExp createConcatenation(RegExp r1, RegExp r2) {
  return RegExp(RegExpEnum::kConcatenation, r1, r2);
}

RegExp createDot() {
  return RegExp(RegExpEnum::kDot);
}

RegExp createLiteral(RegExp::literalType literal) {
  return RegExp(RegExpEnum::kLiteral, literal);
}

RegExp createOneOrMore(RegExp r) {
  return RegExp(RegExpEnum::kOneOrMore, r);
}

RegExp createUnion(RegExp r1, RegExp r2) {
  return RegExp(RegExpEnum::kUnion, r1, r2);
}

RegExp createZeroOrOne(RegExp r) {
  return RegExp(RegExpEnum::kZeroOrOne, r);
}

}  // namespace resyntax

}  // namespace tinygrep
