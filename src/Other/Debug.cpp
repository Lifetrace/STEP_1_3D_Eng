#include "Other/Debug.hpp"
#include <iostream>

void EnableAnsiColors() {
#ifdef _WIN32
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  if (hOut == INVALID_HANDLE_VALUE) {
    return;
  }

  DWORD dwMode = 0;

  if (!GetConsoleMode(hOut, &dwMode)) {
    return;
  }

  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
#endif
}

namespace LoopEngine {

void Debug::Log(std::string msg) {
  std::cout << LOOP_DEBUG_COLOR_GREEN << "[LOG] " << msg
            << LOOP_DEBUG_COLOR_RESET << std::endl;
}

void Debug::Warning(std::string msg) {
  std::cout << LOOP_DEBUG_COLOR_BLUE << "[WARNING] " << msg
            << LOOP_DEBUG_COLOR_RESET << std::endl;
}

void Debug::Error(std::string msg) {
  std::cerr << LOOP_DEBUG_COLOR_RED << "[ERROR] " << msg
            << LOOP_DEBUG_COLOR_RESET << std::endl;
}

void Debug::Init() { EnableAnsiColors(); }

} // namespace LoopEngine
