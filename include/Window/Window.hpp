#pragma once

#include <unordered_map>

class GLFWwindow;

namespace LoopEngine {
class Window {
  int cur_width;
  int cur_height;

  const char *title;

  GLFWwindow *window;

  bool initialized = false;

  int Init(int width, int height, const char *title);

  static std::unordered_map<GLFWwindow *, Window *> inline WindowList;

public:
  Window(int width, int height, const char *title);

  bool IsClose();
  void SetClose(bool value);
  void Terminate();
  void SwapBuf();

  void SetWidth(int width) { cur_width = width; }
  void SetHeight(int height) { cur_height = height; }

  int GetWidth() { return cur_width; }
  int GetHeight() { return cur_height; }

  bool GetStable() { return initialized; }

  static Window *GetWin(GLFWwindow *window_) {
    auto it = WindowList.find(window_);
    if (it == WindowList.end()) {
      return nullptr;
    }
    return it->second;
  }
};
} // namespace LoopEngine
