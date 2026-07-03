#pragma once

#include <vector>

namespace LoopEngine {

struct VertexData {
  std::vector<float> VertPos;
  std::vector<float> VertColors;
  std::vector<float> VertTexCoords;
  std::vector<unsigned int> Indices;
};

struct PrimitivesVerts {
  static std::vector<float> inline cubeVertices = {
        // front face z = 1
        -1.0f, -1.0f,  1.0f, //
         1.0f, -1.0f,  1.0f, //
         1.0f,  1.0f,  1.0f, //

         1.0f,  1.0f,  1.0f, //
        -1.0f,  1.0f,  1.0f, //
        -1.0f, -1.0f,  1.0f, //

        // back face z = -1
         1.0f, -1.0f, -1.0f, //
        -1.0f, -1.0f, -1.0f, //
        -1.0f,  1.0f, -1.0f, //

        -1.0f,  1.0f, -1.0f, //
         1.0f,  1.0f, -1.0f, //
         1.0f, -1.0f, -1.0f, //

        // left face x = -1
        -1.0f, -1.0f, -1.0f, //
        -1.0f, -1.0f,  1.0f, //
        -1.0f,  1.0f,  1.0f, //

        -1.0f,  1.0f,  1.0f, //
        -1.0f,  1.0f, -1.0f, //
        -1.0f, -1.0f, -1.0f, //

        // right face x = 1
         1.0f, -1.0f,  1.0f, //
         1.0f, -1.0f, -1.0f, //
         1.0f,  1.0f, -1.0f, //

         1.0f,  1.0f, -1.0f, //
         1.0f,  1.0f,  1.0f, //
         1.0f, -1.0f,  1.0f, //

        // top face y = 1
        -1.0f,  1.0f,  1.0f, //
         1.0f,  1.0f,  1.0f, //
         1.0f,  1.0f, -1.0f, //

         1.0f,  1.0f, -1.0f, //
        -1.0f,  1.0f, -1.0f, //
        -1.0f,  1.0f,  1.0f, //

        // bottom face y = -1
        -1.0f, -1.0f, -1.0f, //
         1.0f, -1.0f, -1.0f, //
         1.0f, -1.0f,  1.0f, //

         1.0f, -1.0f,  1.0f, //
        -1.0f, -1.0f,  1.0f, //
        -1.0f, -1.0f, -1.0f //
};
  static std::vector<float> inline cubeColors = {
        // front face — red
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        // back face — green
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        // left face — blue
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        // right face — yellow
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        // top face — magenta
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,

        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,

        // bottom face — cyan
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };

};

} // namespace LoopEngine
