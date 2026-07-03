#pragma once

#include <string>
#include <unordered_map>

#include "Other/Data.hpp"

typedef unsigned int uint;

namespace LoopEngine {
class Buffers {
  uint VAO = 0;

  uint VBO_position = 0;
  uint VBO_color = 0;
  uint VBO_texcoord = 0;

  uint EBO = 0;

  VertexData _data;

  bool uploaded = false;

  static std::unordered_map<std::string, Buffers *> BuffersList;

  std::string name;

public:
  Buffers(std::string name) : name(name) {}

  void SetVertPos(std::vector<float> Vpos);
  void SetVertColors(std::vector<float> Vcolor);

  VertexData &GetData() { return _data; }
  const VertexData &GetData() const { return _data; }

  void DrawSolid();
  void DrawLines(); // dev

  int Upload();

  ~Buffers();
};
} // namespace LoopEngine
