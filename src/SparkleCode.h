// copyright 2017
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "./scanner/Scanner.h"
#include "./scanner/Token.h"

class SparkleCode {
 public:
  bool hadError = false;

  void runFile(std::string path);
  void runPrompt();
  void error(int line, std::string message);

 private:
  void run(std::string code);
  void report(int line, std::string where, std::string message);
};
