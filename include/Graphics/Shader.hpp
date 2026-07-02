#pragma once

#include <string>
#include <unordered_map>

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

  static Shader *LoadShader(std::string V_source, std::string F_source,
                            std::string G_source, std::string name);
  static Shader *LoadShader(std::string V_source, std::string F_source,
                            std::string name);

  ~Shader();
};

std::string ReadTextFile(const std::string &file);
} // namespace LoopEngine
