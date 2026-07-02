#include "Application.hpp"
#include "Graphics/Buffers.hpp"
#include "Graphics/Texture.hpp"
#include "Other/Debug.hpp"

int LoopEngine::Application::Start() {
  Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  Events::Init(Window.GetThisWindow());

  Shader *BasicShader = Shader::LoadShader(
      "assets/Shaders/basic.vert", "assets/Shaders/basic.frag", "BasicShader");

  Buffers buffer("Basic");

  buffer.GetData().VertPos = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                              0.0f,  0.0f,  0.5f, 0.0f};

  buffer.GetData().VertColors = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

  buffer.Upload();

  Texture *texture = Texture::LoadTexturePNG("assets/Textures/Test.png");

  if (texture == nullptr) {
    Debug::Warning("Texture is not loaded. Continue with ignore");
  }

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (BasicShader) {
      BasicShader->Use();
    }

    texture->Bind();

    buffer.Draw();

    Window.SwapBuf();
    Events::PollEvents();
  }

  Window.Terminate();

  return 0;
}
