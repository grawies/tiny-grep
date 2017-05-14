#include <iostream>
#include <stdexcept>
#include <string>

#include "enfa.h"
#include "parser.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Error: Bad argument count.\n";
  }
  std::cout << "regex: " << argv[1] << "\n";
  // Currently: assume only regex argument, then search in stdin.
  // parse regexp
  std::string regex = argv[1];
  unsigned int matches = 0;
  try {
    tinygrep::enfa::EpsilonNFA enfa(".*(" + regex + ").*");
    // while there is stdin, search in stdin
    std::string search_line;
    while (std::getline(std::cin, search_line)) {
      // if match is found, output the matching line
      if (enfa.accepts(search_line)) {
        std::cout << search_line << "\n";
        matches++;
      }
    }
  } catch (const std::domain_error& e) {
    std::cout << "Error: Unsupported regex. " << e.what() << "\n";
  }
  std::cout << "Matches: " << matches << std::endl;
  return 0;
}
