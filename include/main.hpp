#pragma once

namespace LoopEngine {
class Application {
public:
  Application() = delete;

  static int Start();

  ~Application() = default;
};
} // namespace LoopEngine
