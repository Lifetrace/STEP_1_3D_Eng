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

  glm::mat4 rotation = glm::mat4(1.0f);

  rotation =
      glm::rotate(rotation, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));

  rotation =
      glm::rotate(rotation, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));

  rotation =
      glm::rotate(rotation, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

  front =
      glm::normalize(glm::vec3(rotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));

  right =
      glm::normalize(glm::vec3(rotation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));

  up = glm::normalize(glm::vec3(rotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

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
