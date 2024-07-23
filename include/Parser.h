#pragma once
#include "Expression.h"
#include "Token.h"
#include <stdexcept>
#include <vector>

class Parser {
public:
  explicit Parser(std::vector<Token> tokens)
      : tokens(std::move(tokens)), current(0) {}

  Expression *parse() { return parseExpression(0); }

private:
  std::vector<Token> tokens;
  size_t current;

  Expression *parseExpression(int precedence) {
    Token token = advance();
    Expression *left = parsePrefix(token);

    while (precedence < getPrecedence(peek().type)) {
      Token token = advance();
      left = parseInfix(left, token);
    }

    return left;
  }

  Expression *parsePrefix(const Token &token) {
    switch (token.type) {
    case Tokentype::INTEGER:
      return new LiteralExpression(token.lexeme);
    case Tokentype::LEFTPEREN:
      return parseGrouping();
    default:
      throw std::runtime_error("Unexpected token");
    }
  }

  Expression *parseInfix(Expression *left, const Token &token) {
    Expression *right = parseExpression(getPrecedence(token.type));
    return new BinaryExpression(left, token.lexeme, right);
  }

  Expression *parseGrouping() {
    Expression *expr = parseExpression(0);
    if (!match(Tokentype::RIGHTPEREN)) {
      throw std::runtime_error("Expected ')'");
    }
    return expr;
  }

  int getPrecedence(Tokentype type) const {
    switch (type) {
    case Tokentype::PLUS:
    case Tokentype::MINUS:
      return 1;
    case Tokentype::STAR:
    case Tokentype::SLASH:
      return 2;
    default:
      return 0;
    }
  }

  bool match(Tokentype type) {
    if (check(type)) {
      advance();
      return true;
    }
    return false;
  }

  bool check(Tokentype type) const {
    return !isAtEnd() && tokens[current].type == type;
  }

  Token advance() {
    if (!isAtEnd())
      current++;
    return previous();
  }

  bool isAtEnd() const { return current >= tokens.size(); }

  Token previous() const { return tokens[current - 1]; }

  Token peek() const { return tokens[current]; }
};
