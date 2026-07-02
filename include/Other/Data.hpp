#pragma once

#include <vector>

namespace LoopEngine {

struct VertexData {
  std::vector<float> VertPos;
  std::vector<float> VertColors;
  std::vector<unsigned int> Indices;
};

}
