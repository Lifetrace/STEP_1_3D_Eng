#pragma once
#include <glm/glm.hpp>

namespace LoopEngine {
class Transform {
  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
  glm::vec3 scale = {1.0f, 1.0f, 1.0f};

  glm::vec3 velocity = {0.0f, 0.0f, 0.0f};

  glm::mat4 model;

public:
  Transform() {
    glm::mat4 _model(1.0f);
    model = _model;
  }

  void MoveTo(glm::vec3 position) { this->position = position; }
  void DeltaMoveTo(glm::vec3 delta_position) { position += delta_position; }

  void RotateTo(glm::vec3 rotation) { this->rotation = rotation; }
  void DeltaRotateTo(glm::vec3 delta_rotation) {
    this->rotation += delta_rotation;
  }

  void ScaleTo(glm::vec3 scale) { this->scale = scale; }
  void DeltaScaleTo(glm::vec3 delta_scale) { this->scale += delta_scale; }

  glm::vec3 GetPosition() { return position; }
  glm::vec3 GetRotation() { return rotation; }
  glm::vec3 GetScale() { return scale; }

  glm::mat4 GetMat() { return model; }

  void Update();

  ~Transform() = default;
};

} // namespace LoopEngine
