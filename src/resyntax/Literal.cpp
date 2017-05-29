#include "Literal.h"

namespace tinygrep {

namespace resyntax {

Literal::Literal(const std::string& expr) {
  if (expr[0] == '\\') {
    expr_ = expr.substr(1);
  } else if (expr[0] == '[' && expr[expr.length()-1] == ']') {
    // Grab the characters within the bracket expression.
    expr_ = expr.substr(1, expr.length()-2);
  } else {
    expr_ = expr;
  }
}

Literal::Literal(const char lit) : expr_(std::string(1, lit)) {
  // TODO
}

bool Literal::matches(const char lit, const size_t offset) const {
  if (expr_ == "..") {
    return true;
  }
  // Check for negation.
  if (offset == 0 && expr_[0] == '^') {
    return !matches(lit, 1);
  }
  for (auto cp = expr_.begin() + offset; cp != expr_.end(); ++cp) {
    if (*cp == lit) {
      return true;
    }
  }
  return false;
}

std::string Literal::to_string() const {
  return expr_;
}

}  // namespace resyntax

}  // namespace tinygrep
