// copyright 2017
#include <iostream>
#include <string>
#include <vector>
#include "./config.h"
#include "./SparkleCode.h"

int main(int argc, char *argvC[]) {
  std::vector<std::string> argv(argvC, argvC + argc);

  // create interpreter
  SparkleCode interp{};

  if (argc > 2) {  // to many arguments
    std::cout << "Usage: SparkleCode [script]" << std::endl;
  } else if (argc == 2) {
    if (argv[1] == "-v") {
      std::cout << "Version " << VERSION_MAJOR << "."
        << VERSION_MINOR << std::endl;
    } else {
      try {
        interp.runFile(argv[1]);
      } catch(char const * msg) {  // catch file loading error
        std::cout << msg;
        return -1;
      }
    }
  } else {
    interp.runPrompt();
  }
  return 0;
}
