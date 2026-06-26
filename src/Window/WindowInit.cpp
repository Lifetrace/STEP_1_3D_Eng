#include "Window/Events.hpp"
#include "Window/Window.hpp"

#include "Other/CallBacks.hpp"
#include "Other/Debug.hpp"
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

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
}
bool LoopEngine::Window::IsClose() {
  return (bool)glfwWindowShouldClose(window);
}
void LoopEngine::Window::SetClose(bool value) {
  glfwSetWindowShouldClose(window, (int)value);
}
void LoopEngine::Window::SwapBuf() { glfwSwapBuffers(window); }

// CallBacks.hpp Init
void LoopEngine::CallBack::frame_buffersize_callback(GLFWwindow *window,
                                                     int width, int height) {
  LoopEngine::Window *win_ = LoopEngine::Window::GetWin(window);
  win_->SetHeight(height);
  win_->SetWidth(width);
  glViewport(0, 0, width, height);
#ifdef LOOP_ENABLE_DEBUG_WINDOWSIZE
  Debug::Log("Window Size changed -> " + std::to_string(win_->GetWidth()) +
             ":" + std::to_string(win_->GetHeight()));
#endif
}
