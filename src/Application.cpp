#include "Application.hpp"
#include "GLFW/glfw3.h"
#include "Graphics/Mesh.hpp"
#include "Graphics/Texture.hpp"
#include "Other/Camera.hpp"
#include "Other/Debug.hpp"
#include "Window/Events.hpp"
#include "glm/ext/vector_float3.hpp"
#include <string>

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
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (Events::justPressed(GLFW_KEY_TAB)) {
      Window.SetCursorLocked(!Events::_cursor_locked);
    }

    // Camera Rotation
    if (Events::_cursor_locked) {
      cam.GetTransform().DeltaRotateTo(
          glm::vec3(-Events::dY, -Events::dX, 0.0f) * cam.GetSens());
    }
    if (cam.GetTransform().IsRotationChanged()) {
      cam.UpdateVectors();
    }

    // Camera Movement
    float moveSpeed = 3.0f;
    glm::vec3 moveDirection = glm::vec3(0.0f);

    if (Events::isPressing(GLFW_KEY_W)) {
      moveDirection += cam.GetFront();
    }
    if (Events::isPressing(GLFW_KEY_S)) {
      moveDirection -= cam.GetFront();
    }
    if (Events::isPressing(GLFW_KEY_A)) {
      moveDirection -= cam.GetRight();
    }
    if (Events::isPressing(GLFW_KEY_D)) {
      moveDirection += cam.GetRight();
    }

    if (glm::length(moveDirection) > 0.0f) {
      moveDirection = glm::normalize(moveDirection);
      cam.GetTransform().DeltaMoveTo(moveDirection * moveSpeed *
                                     Events::deltaTime);
    }

    // Draw Mesh as Solid
    mesh1.DrawAsSolid();

    Window.SwapBuf();
    Events::PollEvents();
  }

  Window.Terminate();

  return 0;
}
