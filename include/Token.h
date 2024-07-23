#pragma once
#include <string>

enum class Tokentype {
  FLOAT,
  FL,
  INTEGER,
  INT,
  STR,
  PLUS,
  MINUS,
  STAR,
  SLASH,
  RIGHTPEREN,
  RIGHTBRACE,
  LEFTPEREN,
  LEFTBRACE,
  SEMICOLON,
  IDENTIFIER,

  CARRIGERETURN,
  WHITESPACE,
  UNKNOWN
};
struct Token {
  Tokentype type;
  std::string lexeme;
  int line;
  int column;

  Token(Tokentype type, std::string lexeme, int line, int column)
      : type(type), lexeme(std::move(lexeme)), line(line), column(column) {}
};
