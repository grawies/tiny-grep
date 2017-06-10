#include "RegExp.h"

namespace tinygrep {

namespace resyntax {

RegExp::RegExp() : RegExp::RegExp(RegExpEnum::kEmpty) {}

RegExp::RegExp(RegExpEnum type) : type_(type), r1_(nullptr), r2_(nullptr), literal_("xxx") {}

RegExp::RegExp(RegExpEnum type, literalType literal) : RegExp::RegExp(type) {
  literal_ = literal;
}

RegExp::RegExp(RegExpEnum type, const RegExp& r1) : RegExp::RegExp(type) {
  r1_ = std::make_shared<RegExp>(r1);
}

RegExp::RegExp(RegExpEnum type, const RegExp& r1, const RegExp& r2) : RegExp::RegExp(type, r1) {
  r2_ = std::make_shared<RegExp>(r2);
}

RegExpEnum RegExp::getType() const {
  return type_;
}

const RegExp& RegExp::getR1() const {
  return *r1_;
}

const RegExp& RegExp::getR2() const {
  return *r2_;
}

RegExp::literalType RegExp::getLiteral() const {
  return literal_;
}

}  // namespace resyntax

}  // namespace tinygrep
