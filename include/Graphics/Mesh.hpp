#pragma once

#include "Graphics/Buffers.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Other/Data.hpp"
#include "Other/Debug.hpp"
#include "Other/Transform.hpp"

enum class PrimitiveType { Plane, Cube, Cylinder, Cone, Sphere };

namespace LoopEngine {
class Mesh {
  std::string name;

  Shader *shader = nullptr;
  Buffers *buffer = nullptr;
  Texture *texture = nullptr;

  Transform transform;

  static std::unordered_map<std::string, Mesh *> inline MeshList;

  PrimitiveType type;

  bool type_selected = false;
  bool shader_loaded = false;
  bool data_installed = false;
  bool created = false;

  void SetData(VertexData data) {
    if (!buffer) {
      Debug::Error("Mesh (" + name + ") buffer is nullptr!");
      return;
    }

    buffer->GetData() = data;
    data_installed = true;
  }

public:
  Mesh(std::string name);

  void SetType(PrimitiveType type) {
    if (!type_selected) {
      this->type = type;
      type_selected = true;
    }
  }

  void SetShader(Shader *shader) {
    if (shader != nullptr) {
      this->shader = shader;
      shader_loaded = true;
    } else {
      Debug::Error("Loaded null shader to " + name + " mesh");
    }
  }

  void Create();

  void UpdateTransform();

  void DrawAsSolid();
  void DrawAsLines();
};

} // namespace LoopEngine
