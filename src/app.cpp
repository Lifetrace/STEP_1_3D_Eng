#include "main.hpp"

#include "Other/GLINC.hpp"
#include "Window/Window.hpp"

int LoopEngine::Application::Start() {
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
