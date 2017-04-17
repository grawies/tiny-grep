#ifndef TINYGREP_RESYNTAX_REGEXP_H_
#define TINYGREP_RESYNTAX_REGEXP_H_

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
  typedef char literalType;

  RegExp();
  explicit RegExp(RegExpEnum type);
  RegExp(RegExpEnum type, literalType literal);
  RegExp(RegExpEnum type, RegExp r1);
  RegExp(RegExpEnum type, RegExp r1, RegExp r2);
  RegExp(const RegExp& r);
  RegExp(RegExp&& r);

  ~RegExp();

  RegExp& operator= (const RegExp& r);
  RegExp& operator= (RegExp&& r);

  RegExpEnum getType() const;
  RegExp getR1() const;
  RegExp getR2() const;
  literalType getLiteral() const;

 private:
  RegExpEnum type_;
  RegExp *r1_, *r2_;
  literalType literal_;
  void clear_state();
  void copy_state(const RegExp& r);
};

}

#endif // TINYGREP_RESYNTAX_REGEXP_H
