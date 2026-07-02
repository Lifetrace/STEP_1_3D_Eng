#include "Graphics/GLINC.hpp"
#include "Graphics/Shader.hpp"

#include "Other/Debug.hpp"

#include <fstream>
#include <sstream>
#include <string>

std::string LoopEngine::ReadTextFile(const std::string &file) {
  std::fstream in(file, std::ios::in);

  if (!in) {
    Debug::Error("Cannot read file -> " + file);
    return "";
  }

  std::ostringstream ss;
  ss << in.rdbuf();

  return ss.str();
}

int LoopEngine::Shader::CheckShaderCompile(uint id) {
  int success = 0;

  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(id, 1024, nullptr, infoLog);

    std::string info = infoLog;

    Debug::Error("Shader compile error: " + info);

    glDeleteShader(id);

    return -1;
  }

  return 0;
}
int LoopEngine::Shader::CheckProgramCompile(uint id) {
  int success = 0;

  glGetShaderiv(id, GL_LINK_STATUS, &success);

  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(id, 1024, nullptr, infoLog);

    std::string info = infoLog;

    Debug::Error("Shader compile error: " + info);

    glDeleteProgram(id);

    return -1;
  }
  return 0;
}

LoopEngine::Shader::Shader(uint id, std::string name) : id(id), name(name) {}

LoopEngine::Shader *LoopEngine::Shader::LoadShader(std::string V_source,
                                                   std::string F_source,
                                                   std::string G_source,
                                                   std::string name) {

  // Get String Code from file paths (also debug)
  std::string V_string = ReadTextFile(V_source);
  if (V_string.empty()) {
    Debug::Error("Vertex shader file is empty or not found: " + V_source);
    return nullptr;
  }

  std::string F_string = ReadTextFile(F_source);
  if (F_string.empty()) {
    Debug::Error("Fragment shader file is empty or not found: " + F_source);
    return nullptr;
  }

  std::string G_string = ReadTextFile(G_source);
  if (G_string.empty()) {
    Debug::Error("Geometry shader file is empty or not found: " + G_source);
    return nullptr;
  }

  // Convert String code from string to const char*
  const char *V_char = V_string.c_str();
  const char *F_char = F_string.c_str();
  const char *G_char = G_string.c_str();

  uint V_id, F_id, G_id; // shader ids

  // Create vertex Shader and check compile status
  V_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(V_id, 1, &V_char, nullptr);
  glCompileShader(V_id);

  if (LoopEngine::Shader::CheckShaderCompile(V_id) != 0) {
    return nullptr;
  }

  // Create fragment Shader and check compile status
  F_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(F_id, 1, &F_char, nullptr);
  glCompileShader(F_id);

  if (LoopEngine::Shader::CheckShaderCompile(F_id) != 0) {
    return nullptr;
  }

  // Create geometry Shader and check compile status
  G_id = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(G_id, 1, &G_char, nullptr);
  glCompileShader(G_id);

  if (LoopEngine::Shader::CheckShaderCompile(G_id) != 0) {
    return nullptr;
  }

  uint Pr_id; // shader program id

  // Create shader program
  Pr_id = glCreateProgram();

  glAttachShader(Pr_id, V_id); // attach program with vertex shader
  glAttachShader(Pr_id, F_id); // attach program with fragment shader
  glAttachShader(Pr_id, G_id); // attach program with geometry shader

  glLinkProgram(Pr_id); // link program

  // Check program compile
  if (Shader::CheckProgramCompile(Pr_id) != 0) {
    return nullptr;
  }

  // Delete useless (for now) shaders
  glDeleteShader(V_id);
  glDeleteShader(F_id);
  glDeleteShader(G_id);

  ShaderList[Pr_id] = new Shader(Pr_id, name);

  ShaderList[Pr_id]->V_code = V_char;
  ShaderList[Pr_id]->F_code = F_char;
  ShaderList[Pr_id]->G_code = G_char;

  return ShaderList[Pr_id];
}
LoopEngine::Shader *LoopEngine::Shader::LoadShader(std::string V_source,
                                                   std::string F_source,
                                                   std::string name) {

  // Get String Code from file paths (also debug)
  std::string V_string = ReadTextFile(V_source);
  std::string F_string = ReadTextFile(F_source);

  if (V_string.empty() or F_string.empty()) {
    if (V_string.empty()) {
      Debug::Error("Vertex shader file is empty or not found: " + V_source);
    }

    if (F_string.empty()) {
      Debug::Error("Fragment shader file is empty or not found: " + F_source);
    }

    return nullptr;
  }

  // Convert String code from string to const char*
  const char *V_char = V_string.c_str();
  const char *F_char = F_string.c_str();

  uint V_id, F_id; // shader ids

  // Create vertex Shader and check compile status
  V_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(V_id, 1, &V_char, nullptr);
  glCompileShader(V_id);

  if (LoopEngine::Shader::CheckShaderCompile(V_id) != 0) {
    return nullptr;
  }

  // Create fragment Shader and check compile status
  F_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(F_id, 1, &F_char, nullptr);
  glCompileShader(F_id);

  if (LoopEngine::Shader::CheckShaderCompile(F_id) != 0) {
    return nullptr;
  }

  uint Pr_id; // shader program id

  // Create shader program
  Pr_id = glCreateProgram();

  glAttachShader(Pr_id, V_id); // attach program with vertex shader
  glAttachShader(Pr_id, F_id); // attach program with fragment shader

  glLinkProgram(Pr_id); // link program

  // Check program compile
  if (Shader::CheckProgramCompile(Pr_id) != 0) {
    return nullptr;
  }

  // Delete useless (for now) shaders
  glDeleteShader(V_id);
  glDeleteShader(F_id);

  ShaderList[Pr_id] = new Shader(Pr_id, name);

  ShaderList[Pr_id]->V_code = V_char;
  ShaderList[Pr_id]->F_code = F_char;
  ShaderList[Pr_id]->G_code = nullptr;

  return ShaderList[Pr_id];
}

void LoopEngine::Shader::Use() {
  auto it = ShaderList.find(this->id);

  if (it != ShaderList.end() && it->second != nullptr) {
    glUseProgram(this->id);
  }
}

LoopEngine::Shader::~Shader() { glDeleteProgram(id); }
