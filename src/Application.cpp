#include "Application.hpp"
#include "GLFW/glfw3.h"
#include "Graphics/Mesh.hpp"
#include "Graphics/Texture.hpp"
#include "Other/Camera.hpp"
#include "Other/Debug.hpp"
#include "Window/Events.hpp"
#include "glm/ext/vector_float3.hpp"

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

  Camera cam({0.0f, 0.0f, 3.0f}, 60.0f, "cam1");

  while (!Window.IsClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (Events::justPressed(GLFW_KEY_TAB)) {
      Window.SetCursorLocked(!Events::_cursor_locked);
    }


    // Cube Rotation
    if (Events::isPressing(GLFW_KEY_RIGHT)) {
      mesh1.GetTransform().DeltaRotateTo(glm::vec3(0.0f, 90.0f, 0.0f) *
                                         Events::deltaTime);
    }
    if (Events::isPressing(GLFW_KEY_LEFT)) {
      mesh1.GetTransform().DeltaRotateTo(glm::vec3(0.0f, -90.0f, 0.0f) *
                                         Events::deltaTime);
    }

    // Camera Movement
    if (Events::isPressing(GLFW_KEY_W)) {
      cam.GetTransform().DeltaMoveTo(glm::vec3(0.0f, 0.0f, -1.0f) *
                                     Events::deltaTime);
    }
    if (Events::isPressing(GLFW_KEY_S)) {
      cam.GetTransform().DeltaMoveTo(glm::vec3(0.0f, 0.0f, 1.0f) *
                                     Events::deltaTime);
    }
    if (Events::isPressing(GLFW_KEY_A)) {
      cam.GetTransform().DeltaMoveTo(glm::vec3(-1.0f, 0.0f, 0.0f) *
                                     Events::deltaTime);
    }
    if (Events::isPressing(GLFW_KEY_D)) {
      cam.GetTransform().DeltaMoveTo(glm::vec3(1.0f, 0.0f, 0.0f) *
                                     Events::deltaTime);
    }

    cam.GetTransform().DeltaRotateTo({0.0f, 0.5f, 0.0f});
    cam.UpdateVectors();

    mesh1.DrawAsSolid();

    Window.SwapBuf();
    Events::PollEvents();
  }

  Window.Terminate();

  return 0;
}
