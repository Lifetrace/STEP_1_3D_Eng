#include "Debug.hpp"
#include <iostream>

namespace LoopEngine {

void Debug::Log(std::string msg) {
  std::cout << LOOP_COLOR_GREEN << "[LOG] " << msg << LOOP_COLOR_RESET
            << std::endl;
}

void Debug::Warning(std::string msg) {
  std::cout << LOOP_COLOR_BLUE << "[WARNING] " << msg << LOOP_COLOR_RESET
            << std::endl;
}

void Debug::Error(std::string msg) {
  std::cerr << LOOP_COLOR_RED << "[ERROR] " << msg << LOOP_COLOR_RESET
            << std::endl;
}

} // namespace LoopEngine
