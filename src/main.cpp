#include "Window/Window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

int main() {

  LoopEngine::Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    Window.SwapBuf();
    glfwPollEvents();
  }

  Window.Terminate();

  return 0;
}
