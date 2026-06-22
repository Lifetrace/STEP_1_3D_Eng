#pragma once

class GLFWwindow;

namespace LoopEngine {
class Window {
  int cur_width;
  int cur_height;

  const char *title;

  GLFWwindow *window;

  bool initialized = false;

  int Init(int width, int height, const char *title);

public:
  Window(int width, int height, const char *title);

  bool IsClose();
  void SetClose(bool value);
  void Terminate();
  void SwapBuf();

  void SetWidth(int width) { cur_width = width; }
  void SetHeight(int height) { cur_height = height; }

  int GetWidth(int width) { return cur_width; }
  int GetHeight(int height) { return cur_height; }

  bool GetStable() { return initialized; }

};
} // namespace LoopEngine
