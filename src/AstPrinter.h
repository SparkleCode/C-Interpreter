// copyright 2017

#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "./Expr.h"

class AstPrinter : public IVisitExpr {
  private:
  std::stringstream out;

 public:
  std::string print(Expr* e) {
    out.clear();
    e->accept(this);
    return out.str();
  }

  void parenthesise(std::string name, Expr* e1) {
    out << "(" << name;
    e1->accept(this);
    out << ")";
  }

  std::string parenthesise(std::string name, Expr* e1, Expr* e2) {
    out << "(" << name << " ";
    e1->accept(this);
    out << " ";
    e2->accept(this);
    out << ")";
  }

  void visitBinaryExpr(Binary* expr) {
    parenthesise(expr->op.lexeme, expr->left, expr->right);
  }

  void visitGroupingExpr(Grouping* expr) {
    parenthesise("group", expr->expression);
  }

  void visitLiteralExpr(Literal* expr) {
    out << expr->value;
  }

  void visitUnaryExpr(Unary* expr) {
    parenthesise(expr->op.lexeme, expr->right);
  }
};
