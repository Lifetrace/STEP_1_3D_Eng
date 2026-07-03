#pragma once

#include <unordered_map>

class GLFWwindow;

namespace LoopEngine {
class Window {
  int cur_width;
  int cur_height;

  float aspect;

  const char *title;

  GLFWwindow *window;

  bool initialized = false;

  static std::unordered_map<GLFWwindow *, Window *> inline WindowList;

  int Init(int width, int height, const char *title);

public:
  Window(int width, int height, const char *title);

  bool IsClose();
  void SetClose(bool value);
  void Terminate();
  void SwapBuf();

  void SetWidth(int width) { cur_width = width; }
  void SetHeight(int height) { cur_height = height; }

  void SetAspect(float aspect) {
    if (aspect != 0.0f) {
      this->aspect = aspect;
    } else {
      this->aspect = 1.0f;
    }
  }
  float GetAspect() { return this->aspect; }

  int GetWidth() { return cur_width; }
  int GetHeight() { return cur_height; }

  bool GetStable() { return initialized; }

  GLFWwindow *GetThisWindow() { return this->window; }

  Window *GetThis() { return this; }
  static Window *GetWin(GLFWwindow *window_) {
    auto it = WindowList.find(window_);
    if (it == WindowList.end()) {
      return nullptr;
    }
    return it->second;
  }

  ~Window() = default;
};
} // namespace LoopEngine
