#include "Other/Camera.hpp"

#include "Other/Debug.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>

LoopEngine::Camera::Camera(glm::vec3 position, float fov, std::string name)
    : fov(fov), name(name) {
  transform.MoveTo(position);
  isActive = true;

  CameraList.push_back(this);
}

glm::mat4 LoopEngine::Camera::GetView() {
  glm::vec3 position = transform.GetPosition();

  view = glm::lookAt(position, position + front, up);

  return view;
}

glm::mat4 LoopEngine::Camera::GetProj(LoopEngine::Window *win) {
  return glm::perspective(glm::radians(fov), win->GetAspect(), 0.1f, 100.0f);
}

void LoopEngine::Camera::UpdateVectors() {
  glm::vec3 rot = transform.GetRotation();

  // Ограничиваем pitch, чтобы камера не переворачивалась через верх/низ
  if (rot.x > 89.0f) {
    rot.x = 89.0f;
    transform.RotateTo(rot);
  }

  if (rot.x < -89.0f) {
    rot.x = -89.0f;
    transform.RotateTo(rot);
  }

  pitch = glm::radians(rot.x);
  yaw = glm::radians(rot.y);

  front.x = -sin(yaw) * cos(pitch);
  front.y = sin(pitch);
  front.z = -cos(yaw) * cos(pitch);
  front = glm::normalize(front);

  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));

  transform.ResetRotationChanged();
}

LoopEngine::Camera *LoopEngine::Camera::GetActiveCamera() {
  for (int i = 0; i < CameraList.size(); i++) {
    if (CameraList[i]->IsActive()) {
      return CameraList[i];
    }
  }

  Debug::Warning("There is no any active camera in the scene!");

  return nullptr;
}
