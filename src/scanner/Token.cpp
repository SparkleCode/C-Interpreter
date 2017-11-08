// copyright 2017
#include "./Token.h"

Token::Token(TokenType type, std::string lexeme, std::string lit, int line) {
  this->type = type;
  this->lexeme = lexeme;
  this->strLit = lit;
  this->typeLit = Token::literalType::STRING;
  this->line = line;
}

Token::Token(TokenType type, std::string lexeme, double lit, int line) {
  this->type = type;
  this->lexeme = lexeme;
  this->numLit = lit;
  this->typeLit = Token::literalType::NUMBER;
  this->line = line;
}

Token::Token(TokenType type, std::string lexeme, int line) {
  this->type = type;
  this->lexeme = lexeme;
  this->typeLit = Token::literalType::NONE;
  this->line = line;
}
Token::Token() {
  this->typeLit = Token::literalType::NONE;
  this->line = -1;
}

std::ostream& operator<<(std::ostream& os, const Token& tok) {
  os << "Token(";
  os << tok.type;
  switch(tok.typeLit){
    case Token::literalType::NUMBER: os << ", " << tok.numLit; break;
    case Token::literalType::STRING: os << ", \"" << tok.strLit << "\""; break;
    case Token::literalType::NONE: break;
  }
  os << ')';
}
