#pragma once

#include "Other/Transform.hpp"
#include "Window/Window.hpp"

#include <string>

namespace LoopEngine {
class Camera {
  std::string name;

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

  float fov;

  Transform transform;

  static std::vector<Camera *> inline CameraList;

  void UpdateVectors();

  bool isActive = false;

public:
  Camera(glm::vec3 position, float fov, std::string name);

  void RotateTo(glm::vec3 rotation);
  void MoveTo(glm::vec3 position);

  glm::mat4 GetView();
  glm::mat4 GetProj(Window *win);

  std::string GetName() { return name; }

  bool IsActive() { return isActive; }

  static Camera *GetActiveCamera();
};
} // namespace LoopEngine
