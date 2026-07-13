#pragma once

#include "Graphics/GLINC.hpp"

#include "Graphics/Lightning/LightStr.hpp"
#include "Graphics/Lightning/ShadowStr.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Texture.hpp"

#include "Other/Camera.hpp"
#include "Other/Debug.hpp"

#include "Window/Events.hpp"

namespace LoopEngine {
class Application {
public:
  Application() = delete;

  static int Start();

  ~Application() = default;
};
} // namespace LoopEngine
