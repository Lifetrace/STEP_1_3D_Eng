#include "Window/Events.hpp"
#include "Window/Window.hpp"

#include "Other/CallBacks.hpp"
#include "Other/Debug.hpp"

#include "Graphics/GLINC.hpp"
#include <string>

// Window.hpp inits
LoopEngine::Window::Window(int width, int height, const char *title)
    : cur_width(width), cur_height(height), title(title) {
  if (Init(width, height, title) == 0) {
    initialized = true;
    WindowList[this->window] = this;
  }
}

int LoopEngine::Window::Init(int width, int height, const char *title) {
  Debug::Init();

  glfwSetErrorCallback(CallBack::error_callback);

  if (!glfwInit()) {
    Debug::Error("GLFW has NOT been initialized correctly!");
    system("pause");
    return -1;
  }

  Debug::Log("GLFW has been initialized correctly!");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 8);

  window = glfwCreateWindow(width, height, "The Game", nullptr, nullptr);

  if (!window) {
    Debug::Error("Window has NOT been initialized correctly!");
    Terminate();
    system("pause");
    return -1;
  }

  Debug::Log("Window has been initialized correctly!");

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(
      window, LoopEngine::CallBack::frame_buffersize_callback);

  if (!gladLoadGL(glfwGetProcAddress)) {
    Debug::Error("GLAD Proc Address has NOT been loaded correctly!");
    Terminate();
    system("pause");
    return -1;
  }

  Debug::Log("GLAD has been initialized correctly!");

  glViewport(0, 0, width, height);

  return 0;
}
void LoopEngine::Window::Terminate() {
  if (window) {
    glfwDestroyWindow(window);
  }

  glfwTerminate();

  WindowList.erase(window);
}
bool LoopEngine::Window::IsClose() {
  return (bool)glfwWindowShouldClose(window);
}
void LoopEngine::Window::SetClose(bool value) {
  glfwSetWindowShouldClose(window, (int)value);
}
void LoopEngine::Window::SwapBuf() { glfwSwapBuffers(window); }

// Events.hpp Inits

int LoopEngine::Events::Init(GLFWwindow *window) {
  Window *_win = Window::GetWin(window);

  _keys = new bool[LOOP_KEYS_COUNT];
  _frames = new uint[LOOP_KEYS_COUNT];

  memset(_keys, false, LOOP_KEYS_COUNT * sizeof(bool));
  memset(_frames, 0, LOOP_KEYS_COUNT * sizeof(uint));

  glfwSetKeyCallback(window, CallBack::key_callback);
  glfwSetMouseButtonCallback(window, CallBack::mouse_button_callback);
  glfwSetCursorPosCallback(window, CallBack::cursor_position_callback);

  return 0;
}

bool LoopEngine::Events::justPressed(int keycode) {
  if (keycode < 0 or keycode >= LOOP_KEYS_FROM_BUTTONS) {
    return false;
  }

  return _keys[keycode] and (_frames[keycode] == _current);
}
bool LoopEngine::Events::isPressing(int keycode) {
  if (keycode < 0 or keycode >= LOOP_KEYS_FROM_BUTTONS) {
    return false;
  }

  return _keys[keycode];
}

bool LoopEngine::Events::justClicked(int button_code) {
  if (button_code < LOOP_KEYS_FROM_BUTTONS or button_code >= LOOP_KEYS_COUNT) {
    return false;
  }

  return _keys[button_code] && (_frames[button_code] == _current);
}
bool LoopEngine::Events::isHolding(int button_code) {
  if (button_code < LOOP_KEYS_FROM_BUTTONS or button_code >= LOOP_KEYS_COUNT) {
    return false;
  }

  return _keys[button_code];
}

void LoopEngine::Events::PollEvents() {
  dX = 0.0f;
  dY = 0.0f;

  _current++;
  glfwPollEvents();
}

// CallBacks.hpp (for Window.cpp) Init
void LoopEngine::CallBack::frame_buffersize_callback(GLFWwindow *window,
                                                     int width, int height) {
  LoopEngine::Window *win_ = LoopEngine::Window::GetWin(window);

  if (win_ == nullptr)
    return;

  win_->SetHeight(height);
  win_->SetWidth(width);
  glViewport(0, 0, width, height);
#ifdef LOOP_ENABLE_DEBUG_WINDOWSIZE
  Debug::Log("Window Size changed -> " + std::to_string(win_->GetWidth()) +
             ":" + std::to_string(win_->GetHeight()));
#endif
}

// CallBacks.hpp (for Events.cpp) Init
void LoopEngine::CallBack::cursor_position_callback(GLFWwindow *window,
                                                    double xpos, double ypos) {
  if (Events::not_first_frame) {
    Events::dX = xpos - Events::x;
    Events::dY = ypos - Events::y;
  } else {
    Events::not_first_frame = true;
  }
  Events::x = xpos;
  Events::y = ypos;
#ifdef LOOP_ENABLE_CURSOR_DEBUG
  Debug::Log("Cursor coordinates: " + std::to_string(Events::x) + " | " +
             std::to_string(Events::y));
  Debug::Log("Cursor movement: " + std::to_string(Events::dX) + " | " +
             std::to_string(Events::dY));
#endif
}
void LoopEngine::CallBack::key_callback(GLFWwindow *window, int key,
                                        int scancode, int action, int mode) {
  if (action == GLFW_PRESS) {
    Events::_frames[key] = Events::_current;
    Events::_keys[key] = true;
  } else if (action == GLFW_RELEASE) {
    Events::_frames[key] = Events::_current;
    Events::_keys[key] = false;
  }

  return;
}
void LoopEngine::CallBack::mouse_button_callback(GLFWwindow *window, int button,
                                                 int action, int mode) {
  if (action == GLFW_PRESS) {
    Events::_frames[LOOP_KEYS_FROM_BUTTONS + button] = Events::_current;
    Events::_keys[LOOP_KEYS_FROM_BUTTONS + button] = true;
  } else if (action == GLFW_RELEASE) {
    Events::_frames[LOOP_KEYS_FROM_BUTTONS + button] = Events::_current;
    Events::_keys[LOOP_KEYS_FROM_BUTTONS + button] = false;
  }
}
