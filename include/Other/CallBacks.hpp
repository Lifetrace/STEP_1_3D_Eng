#pragma once

#include <iostream>

namespace LoopEngine {
class CallBack {
public:
  CallBack() = delete;

  static void error_callback(int error_code, const char *description) {
    std::cout << "ERR: " << error_code << "\n";
    std::cout << description << "\n";
  }

  ~CallBack() = default;
};
} // namespace LoopEngine
