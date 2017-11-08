// copyright 2017
#pragma once
#include <string>
#include <iostream>
#include "./TokenType.h"

class Token {
 public:
  enum class literalType {
    STRING, NUMBER, NONE
  };

  TokenType type;
  std::string lexeme;
  int line;
  literalType typeLit;
  std::string strLit;
  double numLit;

  Token(TokenType type, std::string lexeme, std::string lit, int line);
  Token(TokenType type, std::string lexeme, double lit, int line);
  Token(TokenType type, std::string lexeme, int line);
  Token();
};

std::ostream& operator<<(std::ostream& os, const Token& tok);
