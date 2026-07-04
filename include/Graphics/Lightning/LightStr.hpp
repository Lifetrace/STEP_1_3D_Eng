#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <Graphics/Lightning/ShadowStr.hpp>
#include <Graphics/Shader.hpp>

namespace LoopEngine {
class Light {
  glm::vec3 lightPos;

  float nearPlane = 1.0f;
  float farPlane = 20.0f;

  glm::mat4 lightProjection =
      glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);

  glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 lightSpaceMatrix = lightProjection * lightView;

  Shader *depthShader = nullptr;
  Shadow *shadow = nullptr;

public:
  Light(glm::vec3 position, Shadow *shadow);
};
} // namespace LoopEngine
