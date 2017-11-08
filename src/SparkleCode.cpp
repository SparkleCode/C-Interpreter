// copyright 2017
#include "SparkleCode.h"

void SparkleCode::runFile(std::string path) {
  std::ifstream in(path, std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    run(contents);
    if (hadError) {
      throw "Program errored";
    }
    return;
  }
  throw "File Loading Error";
}

void SparkleCode::runPrompt() {
  Expr expression = Binary(
    Unary(
      Token(MINUS, "-", 1),
      new Literal("123")),
    Token(STAR, "*", 1),
    new Grouping(new Literal("45.67")));

  expression.accept(AstPrinter());

  std::string response;
  while (true) {
    std::cout << "$ ";
    std::getline(std::cin, response);
    if (response == std::string("exit")) break;
    run(response);
    hadError = false;
  }
}

void SparkleCode::error(int line, std::string message) {
  report(line, "", message);
}

void SparkleCode::run(std::string code) {
  std::cout << code << std::endl << std::endl;
  Scanner scanner(code, this);
  std::vector<Token> tokens = scanner.scanTokens();

  for (Token token : tokens) {
    std::cout << "scanned: " << token << std::endl;
  }
}

void SparkleCode::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << line << "] Error"
   << where << ": " << message << std::endl;
}
