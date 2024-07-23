#pragma once
#include <iostream>
#include <string>

enum class ExprType { LITERAL, BINARY, CONDITIONAL };

struct Expression {
  virtual void print() = 0;
  virtual ~Expression() = default;
  virtual std::string generateArm() = 0;
};

struct LiteralExpression : Expression {
  std::string value;
  explicit LiteralExpression(std::string value) : value(std::move(value)) {}

  void print() override { std::cout << "Literal: " << value << std::endl; }
  std::string generateArm() override { return "    MOV W0, #" + value + "\n"; }
};

struct BinaryExpression : Expression {
  Expression *left;
  std::string op;
  Expression *right;

  BinaryExpression(Expression *left, std::string op, Expression *right)
      : left(left), op(std::move(op)), right(right) {}

  void print() override {
    std::cout << "Binary Expression: (" << std::endl;
    left->print();
    std::cout << " " << op << " ";
    right->print();
    std::cout << ")" << std::endl;
  }

  std::string generateArm() override {
    std::string output = left->generateArm() + "    STR W0, [SP, #-16]!\n";
    output += right->generateArm() + "    STR W0, [SP, #-16]!\n";
    output += "    LDR W1, [SP], #16\n    LDR W0, [SP], #16\n";
    if (op == "+") {
      output += "    ADD W0, W0, W1\n";
    } else if (op == "-") {
      output += "    SUB W0, W0, W1\n";
    }
    return output;
  }

  ~BinaryExpression() {
    delete left;
    delete right;
  }
};

struct ConditionalExpression : Expression {
  Expression *condition;
  Expression *thenExpr;
  Expression *elseExpr;

  ConditionalExpression(Expression *condition, Expression *thenExpr,
                        Expression *elseExpr)
      : condition(condition), thenExpr(thenExpr), elseExpr(elseExpr) {}

  void print() override {
    std::cout << "Conditional Expression: (if ";
    condition->print();
    std::cout << " then ";
    thenExpr->print();
    std::cout << " else ";
    elseExpr->print();
    std::cout << ")" << std::endl;
  }

  ~ConditionalExpression() {
    delete condition;
    delete thenExpr;
    delete elseExpr;
  }
};

std::ostream &operator<<(std::ostream &os, Expression &expr) {
  expr.print();
  return os;
}
