#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include <string>
#include <unordered_map>

#include <glm/mat4x4.hpp>

typedef unsigned int uint;

namespace LoopEngine {
class Shader {
  uint id = 0;

  std::string name;

  const char *V_code;
  const char *F_code;
  const char *G_code;

  static std::unordered_map<uint, Shader *> inline ShaderList;

  static int CheckShaderCompile(uint id);
  static int CheckProgramCompile(uint id);

public:
  Shader(uint id, std::string name);

  void Use();

  uint GetID() { return this->id; }

  std::string GetName() { return this->name; }

 void SetMat4x4(std::string name, glm::mat4x4 mat);

  static Shader *LoadShader(std::string V_source, std::string F_source,
                            std::string G_source, std::string name);
  static Shader *LoadShader(std::string V_source, std::string F_source,
                            std::string name);

  ~Shader();
};

std::string ReadTextFile(const std::string &file);
} // namespace LoopEngine
