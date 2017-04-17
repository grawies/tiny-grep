#ifndef TINYGREP_PARSER_H_
#define TINYGREP_PARSER_H_

#include "parser.h"

#include <string>

#include "resyntax/RegExp.h"

namespace tinygrep {

resyntax::RegExp parse(std::string s);

}

#endif // TINYGREP_PARSER_H_
