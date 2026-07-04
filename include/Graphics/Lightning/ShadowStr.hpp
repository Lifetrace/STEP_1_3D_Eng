#pragma once

typedef unsigned int uint;

namespace LoopEngine {
class Shadow {
public:
  const unsigned int SHADOW_WIDTH = 2048;
  const unsigned int SHADOW_HEIGHT = 2048;

  uint depthMapFBO = 0;

  uint depthMap = 0;

  float borderColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  Shadow();
};

} // namespace LoopEngine
