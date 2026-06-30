#pragma once

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#define LOOP_DEBUG_COLOR_RED "\033[31m"
#define LOOP_DEBUG_COLOR_GREEN "\033[32m"
#define LOOP_DEBUG_COLOR_BLUE "\033[34m"
#define LOOP_DEBUG_COLOR_RESET "\033[0m"

namespace LoopEngine {

class Debug {
public:
  static void Log(std::string msg);
  static void Warning(std::string msg);
  static void Error(std::string msg);

  static void Init();
};

} // namespace LoopEngine
