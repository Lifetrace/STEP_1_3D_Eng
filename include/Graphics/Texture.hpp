#pragma once

#include <string>
#include <unordered_map>
typedef unsigned int uint;

namespace LoopEngine {
class Texture {
  uint id;

  int width, height;

  static std::unordered_map<uint, Texture *> inline TextureList;

public:
  Texture(uint id, int width, int heght);

  static Texture *LoadTexturePNG(std::string filepath);

  void Bind();

  ~Texture();
};
} // namespace LoopEngine
