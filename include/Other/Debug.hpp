#pragma once

#include <string>

#define LOOP_COLOR_RED "\033[31m"
#define LOOP_COLOR_GREEN "\033[32m"
#define LOOP_COLOR_BLUE "\033[34m"
#define LOOP_COLOR_RESET "\033[0m"

namespace LoopEngine {

class Debug {
public:
  static void Log(std::string msg);
  static void Warning(std::string msg);
  static void Error(std::string msg);
};

} // namespace LoopEngine
