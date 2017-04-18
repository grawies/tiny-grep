#include "RegExp.h"

namespace tinygrep {

namespace resyntax {

RegExp::RegExp() : RegExp::RegExp(RegExpEnum::kEmpty) {}

RegExp::RegExp(RegExpEnum type) : type_(type), r1_(nullptr), r2_(nullptr), literal_('\0') {}

RegExp::RegExp(RegExpEnum type, literalType literal) : RegExp::RegExp(type) {
  literal_ = literal;
}

RegExp::RegExp(RegExpEnum type, RegExp r1) : RegExp::RegExp(type) {
  r1_ = new RegExp(r1);
}

RegExp::RegExp(RegExpEnum type, RegExp r1, RegExp r2) : RegExp::RegExp(type, r1) {
  r2_ = new RegExp(r2);
}

RegExp::RegExp(RegExp const& r) : RegExp::RegExp() {
  copy_state(r);
}

RegExp::RegExp(RegExp&& r) : RegExp::RegExp(r.type_, r.literal_) {
  r1_ = r.r1_;
  r2_ = r.r2_;
  r.clear_state();
}

RegExp::~RegExp() {
  clear_state();
}

RegExp& RegExp::operator= (const RegExp& r) {
  clear_state();
  copy_state(r);
  return *this;
}

RegExp& RegExp::operator= (RegExp&& r) {
  clear_state();
  copy_state(r);
  r.clear_state();
  return *this;
}

RegExpEnum RegExp::getType() const {
  return type_;
}

RegExp RegExp::getR1() const {
  return *r1_;
}

RegExp RegExp::getR2() const {
  return *r2_;
}

RegExp::literalType RegExp::getLiteral() const {
  return literal_;
}

void RegExp::clear_state() {
  type_ = RegExpEnum::kEmpty;
  literal_ = '\0';
  delete r1_;
  r1_ = nullptr;
  delete r2_;
  r2_ = nullptr;
}

void RegExp::copy_state(const RegExp& r) {
  type_ = r.type_;
  literal_ = r.literal_;
  if (r.r1_)
    r1_ = new RegExp(*r.r1_);
  if (r.r2_)
    r2_ = new RegExp(*r.r2_);
}

}  // namespace resyntax

}  // namespace tinygrep
