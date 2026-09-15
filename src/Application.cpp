#include "Application.hpp"
#include "Graphics/Mesh.hpp"
#include "Window/Events.hpp"
#include "glm/ext/vector_float3.hpp"
#include <cmath>

int LoopEngine::Application::Start() {
  Window Window(1280, 720, "The Game");

  if (!Window.GetStable()) {
    return -1;
  }

  Events::Init(Window.GetThisWindow());

  Shader *BasicShader = Shader::LoadShader(
      "assets/Shaders/basic.vert", "assets/Shaders/basic.frag", "Basic");

  Mesh mesh1("cube", &Window);
  mesh1.SetType(PrimitiveType::Cube);
  mesh1.SetShader(BasicShader);
  mesh1.Create();

  mesh1.GetTransform().ScaleTo({0.5f, 0.5f, 0.5f});

  Mesh floorMesh("floor", &Window);
  floorMesh.SetType(PrimitiveType::Cube);
  floorMesh.SetShader(BasicShader);
  floorMesh.Create();

  floorMesh.GetTransform().MoveTo({0.0f, -1.0f, 0.0f});
  floorMesh.GetTransform().ScaleTo({6.0f, 0.05f, 6.0f});

  Mesh meshLight("light source", &Window);
  meshLight.SetType(PrimitiveType::Cube);
  meshLight.SetShader(BasicShader);
  meshLight.Create();

  meshLight.GetTransform().ScaleTo({0.05f, 0.05f, 0.05f});

  Camera cam({0.0f, 0.0f, 3.0f}, 60.0f, "cam1");

  Shadow shadow;
  Light light(glm::vec3(-2.0f, 4.0f, -1.0f), &shadow);

  meshLight.GetTransform().MoveTo(light.GetTransform().GetPosition() +
                                  glm::vec3(0.0f, 0.15f, 0.0f));

  while (!Window.IsClose()) {
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

    // 1. Первый проход: рисуем глубину глазами света
    light.RenderDepth();

    // 2. Второй проход: обычный рендер на экран
    glViewport(0, 0, Window.GetWidth(), Window.GetHeight());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    light.ApplyToShader(BasicShader, &cam);

    light.GetTransform().MoveTo(light.GetTransform().GetPosition() +
                                glm::vec3(sin(Events::time), 0.0f, 0.0f) * Events::deltaTime);

    meshLight.DrawAsSolid();
    meshLight.GetTransform().MoveTo(light.GetTransform().GetPosition() +
                                    glm::vec3(0.0f, 0.3f, 0.0f));
    mesh1.DrawAsSolid();
    floorMesh.DrawAsSolid();

    Window.SwapBuf();
    Events::PollEvents();
  }

  Window.Terminate();

  return 0;
}
