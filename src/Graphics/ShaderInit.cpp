#include "Graphics/GLINC.hpp"
#include "Graphics/Lightning/LightStr.hpp"
#include "Graphics/Lightning/ShadowStr.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Shader.hpp"

#include "Other/Debug.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

// SHADER INITIALIZATION

// Read text file
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

// Shader Compilations
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

  glGetProgramiv(id, GL_LINK_STATUS, &success);

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

// Shader loadings
LoopEngine::Shader::Shader(uint id, std::string name) : id(id), name(name) {}

LoopEngine::Shader *LoopEngine::Shader::LoadShader(std::string V_source,
                                                   std::string F_source,
                                                   std::string G_source,
                                                   std::string name) {

  // Get String Code from file paths (also debug)
  std::string V_string = ReadTextFile(V_source);
  std::string F_string = ReadTextFile(F_source);
  std::string G_string = ReadTextFile(G_source);

  if (V_string.empty() or F_string.empty() or G_string.empty()) {
    if (V_string.empty()) {
      Debug::Error("Vertex shader file is empty or not found: " + V_source);
    }

    if (F_string.empty()) {
      Debug::Error("Fragment shader file is empty or not found: " + F_source);
    }

    if (G_string.empty()) {
      Debug::Error("Geometry shader file is empty or not found: " + F_source);
    }

    Debug::Warning(name +
                   " was not loaded. Rendering will continue without shader.");

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
    Debug::Warning(name +
                   "was not loaded. Rendering will continue without shader.");
    return nullptr;
  }

  Debug::Log(name + ": vertex component has been successfully loaded");

  // Create fragment Shader and check compile status
  F_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(F_id, 1, &F_char, nullptr);
  glCompileShader(F_id);

  if (LoopEngine::Shader::CheckShaderCompile(F_id) != 0) {
    Debug::Warning(name +
                   "was not loaded. Rendering will continue without shader.");
    return nullptr;
  }

  Debug::Log(name + ": fragment component has been successfully loaded");

  // Create geometry Shader and check compile status
  G_id = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(G_id, 1, &G_char, nullptr);
  glCompileShader(G_id);

  if (LoopEngine::Shader::CheckShaderCompile(G_id) != 0) {
    Debug::Warning(name +
                   "was not loaded. Rendering will continue without shader.");
    return nullptr;
  }

  Debug::Log(name + ": geometry component has been successfully loaded");

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

  Debug::Log(name + ": shader program has been successfully loaded");

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

    Debug::Warning(name +
                   " was not loaded. Rendering will continue without shader.");

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
    Debug::Warning(name +
                   "was not loaded. Rendering will continue without shader.");
    return nullptr;
  }

  Debug::Log(name + ": vertex component has been successfully loaded");

  // Create fragment Shader and check compile status
  F_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(F_id, 1, &F_char, nullptr);
  glCompileShader(F_id);

  if (LoopEngine::Shader::CheckShaderCompile(F_id) != 0) {
    Debug::Warning(name +
                   "was not loaded. Rendering will continue without shader.");
    return nullptr;
  }

  Debug::Log(name + ": fragment component has been successfully loaded");

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

  Debug::Log(name + ": shader program has been successfully loaded");

  // Delete useless (for now) shaders
  glDeleteShader(V_id);
  glDeleteShader(F_id);

  ShaderList[Pr_id] = new Shader(Pr_id, name);

  ShaderList[Pr_id]->V_code = V_char;
  ShaderList[Pr_id]->F_code = F_char;
  ShaderList[Pr_id]->G_code = nullptr;

  return ShaderList[Pr_id];
}

// Set mat4 in shader
void LoopEngine::Shader::SetMat4x4(const std::string &name, glm::mat4x4 mat) {
  uint location = glGetUniformLocation(id, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void LoopEngine::Shader::SetVec3(const std::string &name,
                                 const glm::vec3 &value) {
  int location = glGetUniformLocation(id, name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}
void LoopEngine::Shader::SetVec4(const std::string &name,
                                 const glm::vec4 &value) {
  int location = glGetUniformLocation(id, name.c_str());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void LoopEngine::Shader::SetInt(const std::string &name, int value) {
  int location = glGetUniformLocation(id, name.c_str());
  glUniform1i(location, value);
}

// Shader Use
void LoopEngine::Shader::Use() {
  auto it = ShaderList.find(this->id);

  if (it != ShaderList.end() && it->second != nullptr) {
    glUseProgram(this->id);
  }
}

// Delete shader program
LoopEngine::Shader::~Shader() { glDeleteProgram(id); }

// --SHADER INITIALIZATION

// LIGHTNING INITIALIZATION

// Shadow Constructor
LoopEngine::Shadow::Shadow() {
  glGenFramebuffers(1, &depthMapFBO);
  glGenTextures(1, &depthMap);

  glBindTexture(GL_TEXTURE_2D, depthMap);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH,
               SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                         depthMap, 0);

  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Light Constructor
LoopEngine::Light::Light(glm::vec3 position, Shadow *shadow) : shadow(shadow) {

  lightProjection =
      glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);

  transform.MoveTo(position);

  lightView = glm::lookAt(transform.GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f),
                          glm::vec3(0.0f, 1.0f, 0.0f));

  lightSpaceMatrix = lightProjection * lightView;

  // ВАЖНО: сначала vertex, потом fragment
  depthShader = Shader::LoadShader("assets/Shaders/shadow_depth.vert",
                                   "assets/Shaders/shadow_depth.frag", "Depth");
}

// Depth Rendering (Light)
void LoopEngine::Light::RenderDepth() {
  if (shadow == nullptr || depthShader == nullptr) {
    return;
  }

  glViewport(0, 0, shadow->SHADOW_WIDTH, shadow->SHADOW_HEIGHT);
  glBindFramebuffer(GL_FRAMEBUFFER, shadow->depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);

  depthShader->Use();
  depthShader->SetMat4x4("lightSpaceMatrix", lightSpaceMatrix);

  for (Mesh *mesh : Mesh::GetArray()) {
    if (mesh != nullptr) {
      mesh->DrawDepth(depthShader);
    }
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void LoopEngine::Light::ApplyToShader(Shader *shader, Camera *cam) {
  if (shader == nullptr || shadow == nullptr) {
    return;
  }

  shader->Use();

  shader->SetMat4x4("lightSpaceMatrix", lightSpaceMatrix);
  shader->SetVec3("lightPos", transform.GetPosition());

  if (cam != nullptr) {
    glm::vec3 viewPos = cam->GetTransform().GetPosition();
    shader->SetVec3("viewPos", viewPos);
  }

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, shadow->depthMap);
  shader->SetInt("shadowMap", 0);
}
// --LIGHTNING INITIALIZATION
