#include <fstream>
#include <iostream>
#include <string>
#include <limits>

#include <cxxtest/TestSuite.h>

#include "enfa.h"
#include "parser.h"
#include "resyntax/resyntax.h"

class MyTestSuite : public CxxTest::TestSuite {
  public:
    void test1() {
      std::string regexp = "(a|b)*c";
      // Parse a string to a RegExp AST.
      auto ast = tinygrep::parse(regexp);
      TS_ASSERT_EQUALS(ast.getType(), tinygrep::resyntax::RegExpEnum::kConcatenation);
      auto a_or_b_star = ast.getR1();
      auto c = ast.getR2();
      TS_ASSERT_EQUALS(a_or_b_star.getR1().getR2().getType(), tinygrep::resyntax::RegExpEnum::kLiteral);
      // Create a graph representation.
      auto regexp_test_graph = tinygrep::resyntax::to_graph(ast);
      std::ofstream os_regexp("build/test_regexp_graph.gv");
      if (os_regexp.is_open()) {
        os_regexp << regexp_test_graph;
      }
      os_regexp.close(); // Generate EpsilonNFA from AST.
      auto enfautomaton = tinygrep::enfa::EpsilonNFA(ast);
      TS_ASSERT(enfautomaton.accepts("abbaaababc"));
      TS_ASSERT(enfautomaton.accepts("abc"));
      TS_ASSERT(enfautomaton.accepts("bac"));
      TS_ASSERT(enfautomaton.accepts("c"));
      TS_ASSERT(!enfautomaton.accepts("cc"));
      TS_ASSERT(!enfautomaton.accepts("abbaabababab"));
      TS_ASSERT(!enfautomaton.accepts("acc"));
      TS_ASSERT(!enfautomaton.accepts(""));

      auto enfa_test_graph = enfautomaton.to_graph();
      std::ofstream os_enfa("build/test_enfautomaton_graph.gv");
      if (os_enfa.is_open()) {
        os_enfa << enfa_test_graph;
      }
      os_enfa.close();
    }

    void runtestcase(std::string filepath) {
      std::ifstream testcase(filepath);
      bool testcase_file_available = testcase.is_open();
      TS_ASSERT(testcase_file_available);
      if (!testcase_file_available) {
        return;
      }
      // Ignore alphabet.
      testcase.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      // Read regex, create automaton.
      std::string regex;
      std::getline(testcase, regex);
      tinygrep::enfa::EpsilonNFA enfa(".*(" + regex + ").*");
      // Run searches.
      std::string search_line;
      while (getline(testcase, search_line)) {
        bool accept_flag = search_line[0] == '+'
                        || (search_line[0] != '-' && search_line.rfind("/\\") == std::string::npos);
        TS_ASSERT(enfa.accepts(search_line) == accept_flag);
      }
      testcase.close();
    }
     
    void test2() {
      std::string testcase_prefix("testcase"),
                  testcase_postfix(".txt"),
                  testcase_path("test/manual-testcases/");
      std::vector<std::string> testcase_indices = {"1","2","4","5","10","11"};
      for (std::string testcase_id : testcase_indices) {
        runtestcase(testcase_path + testcase_prefix + testcase_id + testcase_postfix);
      }
    }

};
