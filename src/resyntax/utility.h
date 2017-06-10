#ifndef TINYGREP_RESYNTAX_UTILITY_H_
#define TINYGREP_RESYNTAX_UTILITY_H_

#include <map>
#include <stdexcept>
#include <string>

namespace tinygrep {

namespace resyntax {

namespace utility {

namespace {
  const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  std::map<const std::string, const std::string> char_classes = {
    { "alnum", "0-9A-Za-z"},
    { "alpha", "A-Za-z"},
    { "blank", " \t"},
    { "cntrl", "\x00-\x1f\x7f"},
    { "digit", "0-9"},
    { "graph", "0-9A-Za-z\x21-\x2f\x3a-\x40\x5b-\x60\x7b-\x7e"},
    { "lower", "a-z"},
    { "print", "0-9A-Za-z\x21-\x2f\x3a-\x40\x5b-\x60\x7b-\x7e \t"},
    { "punct", "\x21-\x2f\x3a-\x40\x5b-\x60\x7b-\x7e"},
    { "space", "\t\n\x0b\x0c\x0d "},
    { "upper", "A-Z"},
    { "xdigit", "0-9a-fA-F"}
  };
}

std::string GetCharClassName(const std::string& s, const Literal::size_type start_index) {
  if (s.substr(start_index, 2) == "[:") {
    auto index = start_index + 2;
    while(index < s.length()) {
      bool is_letter = false;
      for (char c : ALPHABET) {
        if (s[index] == c) {
          is_letter = true;
          break;
        }
      }
      if (!is_letter) {
        break;
      }
      ++index;
    }
    if (s[index] == ':' && s[index + 1] == ']') {
      return s.substr(start_index + 2, index - start_index - 2);
    }
  }
  throw std::domain_error("String is not in the supported grammar.");
  return "";
}

std::string CharClassToBracketExpr(const std::string& name) {
  return char_classes[name];
}

}  // namespace utility

}  // namespace resyntax

}  // namespace tinygrep

#endif // TINYGREP_RESYNTAX_UTILITY_H
