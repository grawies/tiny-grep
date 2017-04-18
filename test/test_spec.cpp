#include <string>

#include <cxxtest/TestSuite.h>

#include "linkedqueue/Queue.h"
#include "parser.h"
#include "resyntax/resyntax.h"

class MyTestSuite : public CxxTest::TestSuite {
  public:
    void test1() {
      linkedqueue::Queue<int> q;
      if (q.is_empty()) {
        q.enqueue(3);
        q.enqueue(4);
        q.enqueue(5);
      }
      TS_ASSERT_EQUALS(q.size(), 3);
      if (!q.is_empty()) {
        int a = q.pop();
        q.enqueue(a);
      }
      TS_ASSERT_EQUALS(q.pop(), 4);
      TS_ASSERT_EQUALS(q.peek(), 5);
      TS_ASSERT_EQUALS(q.size(), 2);
      TS_ASSERT_EQUALS(q.is_empty(), false);
    }

    void test2() {
      std::string regexp = "(a|b)*c";
      tinygrep::resyntax::RegExp ast = tinygrep::parse(regexp);
      TS_ASSERT_EQUALS(ast.getType(), tinygrep::resyntax::RegExpEnum::kConcatenation);
      tinygrep::resyntax::RegExp a_or_b_star = ast.getR1();
      tinygrep::resyntax::RegExp c = ast.getR2();
      TS_ASSERT_EQUALS(a_or_b_star.getR1().getR2().getType(), tinygrep::resyntax::RegExpEnum::kLiteral);
    }
};
