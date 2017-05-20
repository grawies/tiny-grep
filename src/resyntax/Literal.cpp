#include "Literal.h"

namespace tinygrep {

namespace resyntax {

Literal::Literal(const std::string& expr) : expr_(expr) {
  // TODO
}

Literal::Literal(const char lit) : expr_(std::string(1, lit)) {
  // TODO
}

bool Literal::matches(const char lit) const {
  return expr_ == std::string(1, lit);
}

std::string Literal::to_string() const {
  return expr_;
}

}  // namespace resyntax

}  // namespace tinygrep
