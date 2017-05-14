#ifndef TINYGREP_RESYNTAX_REGEXP_H_
#define TINYGREP_RESYNTAX_REGEXP_H_

#include <memory>

namespace tinygrep {

namespace resyntax {

enum class RegExpEnum {
  kClosure,
  kConcatenation,
  kDot,
  kLiteral,
  kOneOrMore,
  kUnion,
  kZeroOrOne,
  kEmpty,
};

class RegExp {
 public:
  typedef char                 literalType;
  typedef std::shared_ptr<RegExp>     SPtr;

  RegExp();
  explicit RegExp(RegExpEnum type);
  RegExp(RegExpEnum type, literalType literal);
  RegExp(RegExpEnum type, const RegExp& r1);
  RegExp(RegExpEnum type, const RegExp& r1, const RegExp& r2);
  RegExp(const RegExp& r) = default;
  RegExp(RegExp&& r) = default;

  ~RegExp() = default;

  RegExp& operator= (const RegExp& r) = default;
  RegExp& operator= (RegExp&& r) = default;

  RegExpEnum getType() const;
  const RegExp& getR1() const;
  const RegExp& getR2() const;
  literalType getLiteral() const;

 private:
  RegExpEnum type_;
  SPtr r1_, r2_;
  literalType literal_;
  void clear_state();
  void copy_state(const RegExp& r);
};

}  // namespace resyntax

}  // namespace tinygrep

#endif // TINYGREP_RESYNTAX_REGEXP_H
