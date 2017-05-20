#ifndef TINYGREP_RESYNTAX_LITERAL_H_
#define TINYGREP_RESYNTAX_LITERAL_H_

#include <memory>
#include <string>
#include <vector>

namespace tinygrep {

namespace resyntax {

class Literal {
 public:
  typedef std::shared_ptr<Literal> SPtr;

  explicit Literal(const std::string& expr);
  explicit Literal(const char lit);

  bool matches(const char lit) const;
  std::string to_string() const;

 private:
  std::string expr_;
  char start_, end_;
  std::vector<SPtr> subexpressions_;
};

}  // namespace resyntax

}  // namespace tinygrep

#endif // TINYGREP_RESYNTAX_LITERAL_H
