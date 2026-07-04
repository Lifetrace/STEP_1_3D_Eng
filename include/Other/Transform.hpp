#pragma once
#include <glm/glm.hpp>

namespace LoopEngine {
class Transform {
  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
  glm::vec3 scale = {1.0f, 1.0f, 1.0f};

  glm::vec3 velocity = {0.0f, 0.0f, 0.0f};

  glm::mat4 model;

  bool position_changed = true;
  bool rotation_changed = true;
  bool scale_changed = true;

  static bool VecEqual(const glm::vec3 &a, const glm::vec3 &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
  }

  static bool VecZero(const glm::vec3 &v) {
    return v.x == 0.0f && v.y == 0.0f && v.z == 0.0f;
  }

public:
  Transform() { model = glm::mat4(1.0f); }

  // return is any value changed
  bool IsChanged() const {
    return position_changed || rotation_changed || scale_changed;
  }

  // return is some value changed
  bool IsPositionChanged() const { return position_changed; }
  bool IsRotationChanged() const { return rotation_changed; }
  bool IsScaleChanged() const { return scale_changed; }

  // reset states of changing to false
  void ResetChanged() {
    position_changed = false;
    rotation_changed = false;
    scale_changed = false;
  }

  // reset Rotation matrix
  void ResetRotationChanged() { rotation_changed = false; }

  // Transformation functions
  void MoveTo(glm::vec3 new_position) {
    if (VecEqual(position, new_position)) {
      return;
    }

    position = new_position;
    position_changed = true;
  }
  void DeltaMoveTo(glm::vec3 delta_position) {
    if (VecZero(delta_position)) {
      return;
    }

    position += delta_position;
    position_changed = true;
  }

  void RotateTo(glm::vec3 new_rotation) {
    if (VecEqual(rotation, new_rotation)) {
      return;
    }

    rotation = new_rotation;
    rotation_changed = true;
  }
  void DeltaRotateTo(glm::vec3 delta_rotation) {
    if (VecZero(delta_rotation)) {
      return;
    }

    rotation += delta_rotation;
    rotation_changed = true;
  }

  void ScaleTo(glm::vec3 new_scale) {
    if (VecEqual(scale, new_scale)) {
      return;
    }

    scale = new_scale;
    scale_changed = true;
  }
  void DeltaScaleTo(glm::vec3 delta_scale) {
    if (VecZero(delta_scale)) {
      return;
    }

    scale += delta_scale;
    scale_changed = true;
  }

  // Get components
  glm::vec3 GetPosition() const { return position; }
  glm::vec3 GetRotation() const { return rotation; }
  glm::vec3 GetScale() const { return scale; }

  glm::mat4 GetMat() const { return model; }

  // Reset values
  void ResetPosition() { MoveTo({0.0f, 0.0f, 0.0f}); }
  void ResetRotation() { RotateTo({0.0f, 0.0f, 0.0f}); }
  void ResetScale() { ScaleTo({1.0f, 1.0f, 1.0f}); }

  // Applying components to matrix
  void Update();

  ~Transform() = default;
};
} // namespace LoopEngine
