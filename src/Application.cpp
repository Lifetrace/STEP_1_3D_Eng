#include "Application.hpp"
#include "Window/Events.hpp"

int LoopEngine::Application::Start() {
  LoopEngine::Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  Events::Init(Window.GetThisWindow());

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    Window.SwapBuf();
    Events::PollEvents();
  }

  Window.Terminate();

  return 0;
}
