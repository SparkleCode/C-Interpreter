// copyright 2017

#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "./Expr.h"

class AstPrinter : public IVisitExprString {
 public:
  std::string parenthesise(std::string name, Expr*& e1) {
    std::ostringstream os;
    os << "(" << name;
    os << " " << e1->accept(this);
    os << ")";
    return os.str();
  }
  std::string parenthesise(std::string name, Expr*& e1, Expr*& e2) {
    std::ostringstream os;
    os << "(" << name;
    os << " " << e1->accept(this);
    os << " " << e2->accept(this);
    os << ")";
    return os.str();
  }

  std::string visitBinaryExpr(Binary* expr) {
    return parenthesise(expr->op.lexeme, expr->left, expr->right);
  }

  std::string visitGroupingExpr(Grouping* expr) {
    return parenthesise("group", expr->expression);
  }

  std::string visitLiteralExpr(Literal* expr) {
    return expr->value;
  }

  std::string visitUnaryExpr(Unary* expr) {
    return parenthesise(expr->op.lexeme, expr->right);
  }
};
