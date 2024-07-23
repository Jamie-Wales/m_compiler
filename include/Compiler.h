#pragma once
#include "Expression.h"
#include <fstream>

void compile(Expression *ast) {
  auto output = std::ofstream{"example.s"};
  output << ".global _main" << std::endl;
  output << ".align 2" << std::endl;
  output << "_main:" << std::endl;
  output << "    // Prologue" << std::endl;
  output << "    stp x29, x30, [sp, #-16]!" << std::endl;
  output << "    mov x29, sp" << std::endl;
  output << ast->generateArm();
  output << "    // Epilogue" << std::endl;
  output << "    mov w8, #93" << std::endl;
  output << "    svc 0" << std::endl;
}
