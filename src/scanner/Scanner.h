// copyright 2017
#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include "./Token.h"
#include "./TokenType.h"
#include "../SparkleCode.h"

class SparkleCode;

class Scanner {
 private:
  const std::string source;
  std::vector<Token> tokens{};
  int start = 0;
  int current = 0;
  int line = 1;
  SparkleCode *interp;

  void scanToken();

  void addToken(TokenType type);
  void addToken(TokenType type, std::string lit);
  void addToken(TokenType type, double lit);

  char advance();
  bool match(char expected);
  char peek();
  char peekNext();

  bool isAtEnd();
  bool isDigit(char c);
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);

  void number();
  void string();
  void identifier();

  static std::map<std::string, TokenType> keywords;
  static bool keywordsInitDone;

 public:
  Scanner(std::string source, SparkleCode* interp);
  std::vector<Token> scanTokens();
};
