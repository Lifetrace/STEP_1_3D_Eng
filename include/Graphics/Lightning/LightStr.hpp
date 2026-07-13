#pragma once

#include "Other/Transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "Graphics/Lightning/ShadowStr.hpp"
#include "Graphics/Shader.hpp"
#include "Other/Camera.hpp"

namespace LoopEngine {

class Light {
  Transform transform;

  float nearPlane = 1.0f;
  float farPlane = 20.0f;

  glm::mat4 lightProjection;
  glm::mat4 lightView;
  glm::mat4 lightSpaceMatrix;

  Shader *depthShader = nullptr;
  Shadow *shadow = nullptr;

public:
  Light(glm::vec3 position, Shadow *shadow);

  Transform &GetTransform() { return transform; }

  void RenderDepth();
  void ApplyToShader(Shader *shader, Camera *cam);
};

} // namespace LoopEngine
