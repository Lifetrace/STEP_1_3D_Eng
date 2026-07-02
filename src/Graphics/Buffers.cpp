#include "Graphics/Buffers.hpp"
#include "Graphics/GLINC.hpp"
#include "Other/Debug.hpp"
#include <vector>

int LoopEngine::Buffers::Upload() {
  if (_data.VertPos.empty()) {
    Debug::Error(
        name +
        " buffer doesn`t have Vertex Position Array. It can`t be uploaded");
    return -1;
  }

  glCreateVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO_position);

  if (!_data.VertColors.empty()) {
    glGenBuffers(1, &VBO_color);
  } else {
    Debug::Warning(
        name +
        " buffer doesn`t have Color Array. Potential errors are possible");
  }

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
  glBufferData(GL_ARRAY_BUFFER, _data.VertPos.size() * sizeof(float),
               _data.VertPos.data(), GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  if (!_data.VertColors.empty()) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, _data.VertColors.size() * sizeof(float),
                 _data.VertColors.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(1);
  }

  glBindVertexArray(0);

  uploaded = true;
  Debug::Log(name + " buffer has been uploaded successfully");

  return 0;
}
void LoopEngine::Buffers::SetVertPos(std::vector<float> Vpos) {
  this->_data.VertPos = Vpos;
}
void LoopEngine::Buffers::SetVertColors(std::vector<float> Vcolor) {
  this->_data.VertColors = Vcolor;
}

void LoopEngine::Buffers::Draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

LoopEngine::Buffers::~Buffers() {
  if (VAO)
    glDeleteVertexArrays(1, &VAO);

  if (VBO_position)
    glDeleteBuffers(1, &VBO_position);

  if (VBO_color)
    glDeleteBuffers(1, &VBO_color);

  if (EBO)
    glDeleteBuffers(1, &EBO);
}
