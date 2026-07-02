#pragma once

#include <iostream>

class GLFWwindow;

namespace LoopEngine {
class CallBack {

public:
  CallBack() = delete;

  // For Window
  static void error_callback(int error_code, const char *description) {
    std::cout << "ERR: " << error_code << "\n";
    std::cout << description << "\n";
  }
  static void frame_buffersize_callback(GLFWwindow *window, int width,
                                        int height);

  // For Events
  static void cursor_position_callback(GLFWwindow *window, double xpos,
                                       double ypos);
  static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                    int mode);
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mode);

  ~CallBack() = default;
};
} // namespace LoopEngine
