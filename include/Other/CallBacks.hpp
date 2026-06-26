#pragma once

#include <iostream>

class GLFWwindow;

namespace LoopEngine {
class CallBack {

public:
  CallBack() = delete;

  static void error_callback(int error_code, const char *description) {
    std::cout << "ERR: " << error_code << "\n";
    std::cout << description << "\n";
  }
  static void frame_buffersize_callback(GLFWwindow *window, int width,
                                        int height);

  ~CallBack() = default;
};
} // namespace LoopEngine
