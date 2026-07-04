#pragma once

#include "Transform.hpp"
#include "Window/Window.hpp"

#include "CallBacks.hpp"

#include <string>

namespace LoopEngine {
class Camera {
  float sensivity = 2.0f;

  std::string name;

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

  float fov;

  Transform transform;

  static std::vector<Camera *> inline CameraList;

  bool isActive = false;

public:
  void UpdateVectors();

  Camera(glm::vec3 position, float fov, std::string name);

  float GetSens() { return sensivity; }

  Transform &GetTransform() { return transform; }

  glm::mat4 GetView();
  glm::mat4 GetProj(Window *win);

  std::string GetName() { return name; }

  bool IsActive() { return isActive; }

  static Camera *GetActiveCamera();
};
} // namespace LoopEngine
