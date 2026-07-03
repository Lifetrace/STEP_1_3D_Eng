#include "Application.hpp"
#include "Window/Events.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Texture.hpp"
#include "Other/Debug.hpp"
#include "Other/Camera.hpp"

int LoopEngine::Application::Start() {
  Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  Events::Init(Window.GetThisWindow());

  Mesh mesh1("cube", &Window);
  mesh1.SetType(PrimitiveType::Cube);

  Shader *BasicShader = Shader::LoadShader(
      "assets/Shaders/basic.vert", "assets/Shaders/basic.frag", "Basic");
  mesh1.SetShader(BasicShader);

  mesh1.Create();

  mesh1.GetTransform().ScaleTo({0.5f, 0.5f, 0.5f});

  Camera cam({0.0f, 0.0f, -1.0f}, 60.0f, "cam1");

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (Events::isPressing(GLFW_KEY_RIGHT)){
        mesh1.GetTransform().DeltaRotateTo({0.0f, 0.5f, 0.0f});
    }

    mesh1.DrawAsSolid();


    Window.SwapBuf();
    Events::PollEvents();
  }

  system("pause");

  Window.Terminate();

  return 0;
}
