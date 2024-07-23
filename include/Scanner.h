#pragma once
#include "Token.h"
#include <regex>
#include <string>

class Scanner {
public:
  const std::string input;
  std::vector<Token> tokens;
  Scanner(std::string input) : input{input} {}
  std::vector<Token> tokenize();

private:
  int line = 0;
  int row = 0;
  const std::vector<std::pair<std::regex, Tokentype>> regexList = {
      {std::regex(R"(\d+\.\d*f?)"), Tokentype::FLOAT},
      {std::regex(R"(\d+)"), Tokentype::INTEGER},
      {std::regex(R"("[^"]*")"), Tokentype::STR},
      {std::regex(R"(\+)"), Tokentype::PLUS},
      {std::regex(R"(-)"), Tokentype::MINUS},
      {std::regex(R"(\*)"), Tokentype::STAR},
      {std::regex(R"(/)"), Tokentype::SLASH},
      {std::regex(R"(\))"), Tokentype::RIGHTPEREN},
      {std::regex(R"(\})"), Tokentype::RIGHTBRACE},
      {std::regex(R"(\()"), Tokentype::LEFTPEREN},
      {std::regex(R"(\{)"), Tokentype::LEFTBRACE},
      {std::regex(R"(;)"), Tokentype::SEMICOLON},
      {std::regex(R"([a-zA-Z_]\w*)"), Tokentype::IDENTIFIER},
      {std::regex(R"(\n|\r|$)"), Tokentype::CARRIGERETURN},
      {std::regex(R"(\s+)"), Tokentype::WHITESPACE},
      {std::regex(R"(int)"), Tokentype::INT},
      {std::regex(R"(float)"), Tokentype::FL},
  };

  Tokentype getTokenType(const std::string &captureGroup) const;
};
