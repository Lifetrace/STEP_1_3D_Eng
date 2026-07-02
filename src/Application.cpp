#include "Application.hpp"

int LoopEngine::Application::Start() {
  Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  Events::Init(Window.GetThisWindow());

  Shader *BasicShader = Shader::LoadShader(
      "assets/Shaders/basic.vert", "assets/Shaders/basic.frag", "BasicShader");

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    BasicShader->Use();

    Window.SwapBuf();
    Events::PollEvents();
  }

  Window.Terminate();

  return 0;
}
