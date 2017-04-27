#include <fstream>
#include <string>

#include <cxxtest/TestSuite.h>

#include "linkedqueue/Queue.h"
#include "enfa.h"
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
      // Parse a string to a RegExp AST.
      tinygrep::resyntax::RegExp ast = tinygrep::parse(regexp);
      TS_ASSERT_EQUALS(ast.getType(), tinygrep::resyntax::RegExpEnum::kConcatenation);
      tinygrep::resyntax::RegExp a_or_b_star = ast.getR1();
      tinygrep::resyntax::RegExp c = ast.getR2();
      TS_ASSERT_EQUALS(a_or_b_star.getR1().getR2().getType(), tinygrep::resyntax::RegExpEnum::kLiteral);
      // Create a graph representation.
      std::string regexp_test_graph = tinygrep::resyntax::to_graph(ast);
      std::ofstream os_regexp("build/test_regexp_graph.gv");
      if (os_regexp.is_open()) {
        os_regexp << regexp_test_graph;
      }
      // Generate EpsilonNFA from AST.
      tinygrep::enfa::EpsilonNFA enfautomaton = tinygrep::enfa::EpsilonNFA(ast);
      TS_ASSERT(enfautomaton.accepts("abbaaababc"));
      TS_ASSERT(enfautomaton.accepts("abc"));
      TS_ASSERT(enfautomaton.accepts("bac"));
      TS_ASSERT(enfautomaton.accepts("c"));
      TS_ASSERT(!enfautomaton.accepts("cc"));
      TS_ASSERT(!enfautomaton.accepts("abbaabababab"));
      TS_ASSERT(!enfautomaton.accepts("acc"));
      TS_ASSERT(!enfautomaton.accepts(""));

      std::string enfa_test_graph = enfautomaton.to_graph();
      std::ofstream os_enfa("build/test_enfautomaton_graph.gv");
      if (os_enfa.is_open()) {
        os_enfa << enfa_test_graph;
      }
    }

};
