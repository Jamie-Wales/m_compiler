#include "Scanner.h"
#include <iostream>

std::vector<Token> Scanner::tokenize() {
  size_t position = 0;
  while (position < input.length()) {
    std::smatch match;
    bool foundMatch = false;
    for (const auto &regexPair : regexList) {
      std::string currentSubstring = input.substr(position);
      if (std::regex_search(currentSubstring, match, regexPair.first)) {
        if (match.position() == 0) {
          foundMatch = true;
          Tokentype type = regexPair.second;
          std::string lexeme = match.str();
          if (type == Tokentype::WHITESPACE) {
            row++;
          } else if (type == Tokentype::CARRIGERETURN) {
            line++;
            row = 0;
          } else {
            tokens.emplace_back(type, lexeme, line, row);
          }

          position += match.length();
          break;
        }
      }
    }
    if (!foundMatch) {
      std::cerr << "Unexpected character: " << input[position] << std::endl;
      position++;
    }
  }

  return tokens;
}

Tokentype Scanner::getTokenType(const std::string &lexeme) const {
  for (const auto &regexPair : regexList) {
    if (std::regex_match(lexeme, regexPair.first)) {
      return regexPair.second;
    }
  }
  return Tokentype::UNKNOWN;
}
