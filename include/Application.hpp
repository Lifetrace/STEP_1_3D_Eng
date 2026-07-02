#pragma once

#include "Graphics/GLINC.hpp"
#include "Graphics/Shader.hpp"
#include "Other/Debug.hpp"
#include "Window/Events.hpp"
#include "Window/Window.hpp"

namespace LoopEngine {
class Application {
public:
  Application() = delete;

  static int Start();

  ~Application() = default;
};
} // namespace LoopEngine
