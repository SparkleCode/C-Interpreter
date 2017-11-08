// copyright 2017
#include "./Scanner.h"

bool Scanner::keywordsInitDone = false;
std::map<std::string, TokenType> Scanner::keywords =
  std::map<std::string, TokenType>();
Scanner::Scanner(std::string source, SparkleCode* interp) : source(source) {
  // store reference to interpreter inorder to call error function
  this->interp = interp;

  // if keywords not initialised, do so
  if (!keywordsInitDone) {
    keywordsInitDone = true;
    keywords["and"] = AND;
    keywords["class"] = CLASS;
    keywords["else"] = ELSE;
    keywords["false"] = FALSE;
    keywords["for"] = FOR;
    keywords["fn"] = FN;
    keywords["if"] = IF;
    keywords["or"] = OR;
    keywords["print"] = PRINT;
    keywords["return"] = RETURN;
    keywords["super"] = SUPER;
    keywords["this"] = THIS;
    keywords["var"] = VAR;
    keywords["while"] = WHILE;
  }
}

std::vector<Token> Scanner::scanTokens() {
  // read whole file
  while (!isAtEnd()) {
    // at begining of next lexeme
    start = current;
    scanToken();
  }

  // add end of file token
  tokens.push_back(Token(EofF, "", line));

  return tokens;
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
    // skip whitespace
    case ' ':
    case '\r':
    case '\t': break;

    // new line and skip
    case '\n': line++; break;

    // single character tokens
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;

    // multi character operators
    case '!': addToken(match('=') ?
      NOT_EQUAL : NOT); break;
    case '=': addToken(match('=') ?
      EQUAL_EQUAL : TokenType::EQUAL); break;
    case '<': addToken(match('=') ?
      LESS_EQUAL : LESS); break;
    case '>': addToken(match('=') ?
      GREATER_EQUAL : GREATER); break;

    // is comment or division?
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(SLASH);
      }
      break;

    case '"': string(); break;

    default:
      if (isDigit(c)) {
        number();
      } else if (isAlpha(c)) {
        identifier();
      } else {
        interp->error(line, "unexpected character");
      }
      break;
  }
}

bool Scanner::isAtEnd() {
  // had the end of the file been reached?
  return current >= source.length();
}

char Scanner::advance() {
  // return and consume next character
  current++;
  return source.at(current - 1);
}


void Scanner::addToken(TokenType type) {
  // add token to list of tokens
  std::string text = source.substr(start, current);
  tokens.push_back(Token(type, text, line));
}

void Scanner::addToken(TokenType type, std::string lit) {
  // add token to list of tokens
  std::string text = source.substr(start, current);
  tokens.push_back(Token(type, text, lit, line));
}

void Scanner::addToken(TokenType type, double lit) {
  // add token to list of tokens
  std::string text = source.substr(start, current);
  tokens.push_back(Token(type, text, lit, line));
}

bool Scanner::match(char expected) {
  // consume character and return if it equals expected
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

char Scanner::peek() {
  // get but don't consume character
  if (isAtEnd()) return '\0';
  return source.at(current);
}

char Scanner::peekNext() {
  if (current + 1 >= source.length()) return '\0';
  return source.at(current + 1);
}

void Scanner::string() {
  // loop until end of string
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  // unterminated string
  if (isAtEnd()) {
    interp->error(line, "unterminated string");
    return;
  }

  // consune closing "
  advance();

  // get read string and remove quotes
  std::string value = source.substr(start + 1, current - 2);
  addToken(STRING, value);
}

bool Scanner::isDigit(char c) {
  return c >= '0' && c <= '9';
}

void Scanner::number() {
  while (isDigit(peek())) advance();

  // is decimal
  if (peek() == '.' && isDigit(peekNext())) {
    // consume .
    advance();

    // consume decimal part
    while (isDigit(peek())) advance();
  }

  addToken(NUMBER, atof(source.substr(start, current).c_str()));
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek())) advance();

  std::string text = source.substr(start, current);

  std::map<std::string, TokenType>::iterator pos = keywords.find(text);
  TokenType type;
  if (pos == keywords.end()) {
    type = IDENTIFIER;
  } else {
    type = pos->second;
  }
  addToken(type);
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
  return isAlpha(c) || isDigit(c);
}
