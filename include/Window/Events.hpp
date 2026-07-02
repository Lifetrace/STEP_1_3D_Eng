#pragma once

typedef unsigned int uint;

#define LOOP_KEYS_COUNT 1032
#define LOOP_KEYS_FROM_BUTTONS 1024

class GLFWwindow;

namespace LoopEngine {
class Events {
public:
  Events() = delete;

  static bool inline *_keys = nullptr;
  static uint inline *_frames = nullptr;

  static uint inline _current = 0;

  static float inline dX = 0.0f;
  static float inline dY = 0.0f;

  static float inline x = 0.0f;
  static float inline y = 0.0f;

  static bool inline _cursor_locked = false;
  static bool inline not_first_frame = false;

  static int Init(GLFWwindow *window);
  static void PollEvents();

  static bool justPressed(int keycode);
  static bool isPressing(int keycode);

  static bool justClicked(int button_code);
  static bool isHolding(int button_code);

  static bool Scroll(int axis);

  ~Events() = default;
};
} // namespace LoopEngine
