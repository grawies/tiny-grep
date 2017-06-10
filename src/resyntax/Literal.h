#ifndef TINYGREP_RESYNTAX_LITERAL_H_
#define TINYGREP_RESYNTAX_LITERAL_H_

#include <memory>
#include <string>
#include <vector>

namespace tinygrep {

namespace resyntax {

class Literal {
 public:
  typedef std::string::size_type size_type;

  explicit Literal(const std::string& expr);
  explicit Literal(const char lit);

  bool matches(const char lit) const;
  std::string to_string() const;

 private:
  struct Range {
    char start, end;
  };
  bool negated_ = false;
  std::string expr_;
  std::vector<Range> ranges_;
  std::string singles_;
  void ParseRangeExpression(std::string expr);
};

}  // namespace resyntax

}  // namespace tinygrep

#endif // TINYGREP_RESYNTAX_LITERAL_H
