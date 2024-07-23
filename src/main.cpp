#include "Compiler.h"
#include "Parser.h"
#include "Scanner.h"
#include <fstream>
#include <iterator>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream inputFileStream("./input");
  std::string parsed_file = {std::istreambuf_iterator<char>(inputFileStream),
                             std::istreambuf_iterator<char>()};

  auto scan = Scanner{parsed_file};
  auto tokens = scan.tokenize();
  auto parser = Parser{tokens};
  compile(parser.parse());
}
