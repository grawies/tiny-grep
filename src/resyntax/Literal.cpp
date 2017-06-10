#include "Literal.h"

namespace tinygrep {

namespace resyntax {

Literal::Literal(const std::string& expr) : expr_(expr) {
  if (expr[0] == '\\') {
    singles_ = expr.substr(1);
  } else if (expr[0] == '[' && expr[expr.length()-1] == ']') {
    // Grab the characters within the bracket expression.
    ParseRangeExpression(expr.substr(1, expr.length()-2));
  } else {
    singles_ = expr;
  }
}

Literal::Literal(const char lit) : Literal::Literal(std::string(1, lit)) {}

bool Literal::matches(const char lit) const {
  bool match = false;
  if (expr_ == "..") {
    match = true;
  }
  for (auto cp = singles_.begin(); cp != singles_.end(); ++cp) {
    if (*cp == lit) {
      match = true;
    }
  }
  for (auto range : ranges_) {
    if (range.start <= lit && lit <= range.end) {
      match = true;
    }
  }
  return match != negated_;
}

std::string Literal::to_string() const {
  auto str = (negated_ ? "! " : "") + singles_;
  for (Range range : ranges_) {
    str += " " + std::string(1, range.start) + "-" + std::string(1, range.end);
  }
  return str;
}

void Literal::ParseRangeExpression(std::string expr) {
  std::vector<char> singles_list;
  size_type offset = 0, subexpr_length;
  while (offset < expr.length()) {
    subexpr_length = 1;
    if (offset == 0 && expr[0] == '^') {
      negated_ = true;
    } else if ((offset == 0 || (offset == 1 && negated_)) && expr[offset] == ']') {
      singles_list.push_back(']');
    } else if (offset + 1 < expr.length() && expr.substr(offset, 2) == "[:") {
      // TODO extract char class
      subexpr_length = 0;
    } else if (offset + 2 < expr.length() && expr[offset+1] == '-') {
      // TODO parse range expr
      Range range;
      range.start = expr[offset];
      range.end = expr[offset + 2];
      ranges_.push_back(range);
      subexpr_length = 3;
    } else {
      singles_list.push_back(expr[offset]);
    }
    offset += subexpr_length;
  }
  singles_ = std::string(singles_list.begin(), singles_list.end());
}

}  // namespace resyntax

}  // namespace tinygrep
