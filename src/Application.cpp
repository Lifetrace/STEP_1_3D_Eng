#include "Application.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Texture.hpp"
#include "Other/Debug.hpp"

int LoopEngine::Application::Start() {
  Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  Events::Init(Window.GetThisWindow());

  Mesh mesh1("cube");
  mesh1.SetType(PrimitiveType::Cube);

  Shader *BasicShader = Shader::LoadShader(
      "assets/Shaders/basic.vert", "assets/Shaders/basic.frag", "Basic");

  mesh1.SetShader(BasicShader);

  mesh1.Create();

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    mesh1.DrawAsSolid();

    Window.SwapBuf();
    Events::PollEvents();
  }

  system("pause");

  Window.Terminate();

  return 0;
}
