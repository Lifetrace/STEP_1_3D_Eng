#pragma once

#include "Graphics/Texture.hpp"

typedef unsigned int uint;

namespace LoopEngine {
class Png {
public:
  static uint LoadPNG(const char *file, int *width, int *height);
};
} // namespace LoopEngine
