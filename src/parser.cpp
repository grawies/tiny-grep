#include "parser.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

#include "resyntax/RegExp.h"

namespace tinygrep {

void throw_unsupported_grammar_exception() {
  throw std::domain_error("String is not in the supported grammar.");
}

// Find end of parenthesis subexpr in string:
// returns index s.t. [start_index, index) includes both parentheses.
std::size_t find_matching_parenthesis(const std::string& s, std::size_t start_index, const char open = '(', const char close = ')') {
  std::size_t index = start_index + 1;
  int unmatched_left_parens = 1;
  for (auto it = s.begin() + index; it < s.end() && unmatched_left_parens > 0; ++it, ++index) {
    if (*it == open) {
      ++unmatched_left_parens;
    } else if (*it == close) {
      --unmatched_left_parens;
    }
  }
  if (unmatched_left_parens != 0) {
    throw_unsupported_grammar_exception();
  }
  return index;
}

std::string GetBracketExpression(const std::string& s, const std::size_t start_index, const char open, const char close) {
  std::size_t end_index = find_matching_parenthesis(s, start_index, open, close);
  return s.substr(start_index, end_index - start_index);
}

std::size_t FindBracketNotPrecededBy(const std::string& s, const std::size_t start_index, const char bracket, const char prefix) {
  // scan forward until the first occurrence of bracket not preceeded by prefix
  auto start = s.begin() + start_index;
  for (auto it = start; it != s.end(); ++it) {
    if (*it == bracket && *(it - 1) != prefix) {
      return it - start;
    }
  }
  throw_unsupported_grammar_exception();
  return -1;
}

std::string GetNextSymbol(const std::string& s, std::size_t start_index) {
  char letter = s[start_index];
  std::string symbol = "";
  switch(letter) {
    case '{':
      symbol = GetBracketExpression(s, start_index, '{','}');
      break;
    case '[':
    {
      // Ignore leading ] inside brackets.
      if (s[start_index + 1] == '^') {
        symbol = "[^" + s.substr(start_index + 2, FindBracketNotPrecededBy(s,start_index + 3,']', ':') + 2);
      } else {
        symbol = "[" + s.substr(start_index + 1, FindBracketNotPrecededBy(s,start_index + 2,']', ':') + 2);
      }
      break;
    }
    case '\\':
      symbol = s.substr(start_index, 2);
      break;
    default:
      symbol = std::string(1, letter);
      break;
  }
  return symbol;
}

// Join the regexes in the list with the provided (assumed associative) operator regex.
// Note: Empties the provided vector.
resyntax::RegExp join_regexes(std::vector<resyntax::RegExp>& regex_list, resyntax::RegExpEnum operation) {
  if (regex_list.empty()) {
    return resyntax::RegExp();
  }
  resyntax::RegExp join = regex_list.back();
  regex_list.pop_back();
  while (!regex_list.empty()) {
    join = resyntax::RegExp(operation, regex_list.back(), join);
    regex_list.pop_back();
  }
  return join;
}

void verify_nonempty(std::vector<resyntax::RegExp>& list) {
  if (list.empty()) {
    throw_unsupported_grammar_exception();
  }
}

// Parse the sub-string s[start_index, end_index) to a RegExp AST.
resyntax::RegExp parse_subexpression(const std::string& s, std::size_t start_index, std::size_t end_index) {
  std::vector<resyntax::RegExp> union_list;
  std::vector<resyntax::RegExp> concat_list;
  std::size_t index = start_index;
  while (index < end_index) {
    std::string symbol = GetNextSymbol(s, index);
    char token = symbol[0];
    std::size_t next_index = index + symbol.length();
    switch (token) {
      case '(':
        next_index = find_matching_parenthesis(s, index);
        concat_list.push_back(parse_subexpression(s, index + 1, next_index - 1));
        break;
      case '+':
        verify_nonempty(concat_list);
        concat_list.back() = resyntax::RegExp(resyntax::RegExpEnum::kOneOrMore, concat_list.back());
        break;
      case '?':
        verify_nonempty(concat_list);
        concat_list.back() = resyntax::RegExp(resyntax::RegExpEnum::kZeroOrOne, concat_list.back());
        break;
      case '*':
        verify_nonempty(concat_list);
        concat_list.back() = resyntax::RegExp(resyntax::RegExpEnum::kClosure, concat_list.back());
        break;
      case '|':
        union_list.push_back(join_regexes(concat_list, resyntax::RegExpEnum::kConcatenation));
        concat_list.clear();
        break;
      case '.':
        concat_list.push_back(resyntax::RegExp(resyntax::RegExpEnum::kDot));
        break;
      case '{': // Unimplemented stub. Intentional reset and fall-through.
        next_index = index + 1;
        symbol = "{";
      default:
        concat_list.push_back(resyntax::RegExp(resyntax::RegExpEnum::kLiteral, resyntax::Literal(symbol)));
        break;
    }
    index = next_index;
  }
  if (union_list.empty() && concat_list.empty()) {
    return resyntax::RegExp();
  }
  union_list.push_back(join_regexes(concat_list, resyntax::RegExpEnum::kConcatenation));
  return join_regexes(union_list, resyntax::RegExpEnum::kUnion);
}

resyntax::RegExp parse(const std::string& s) {
  // TODO: Validate s: check if it belongs to the grammar.
  return parse_subexpression(s, 0, s.length());
}

}  // namespace tinygrep
