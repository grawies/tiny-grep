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

bool Literal::matches(const char lit) const {
  for (char c : expr_) {
    if (c == lit) {
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
