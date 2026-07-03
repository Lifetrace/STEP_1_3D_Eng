#include "Graphics/Mesh.hpp"
#include "Other/Camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"

// Mesh init
LoopEngine::Mesh::Mesh(std::string name, Window *window)
    : name(name), window(window) {
  MeshList[name] = this;
}

void LoopEngine::Mesh::Create() {
  if (!type_selected) {
    Debug::Error("Mesh (" + name + ") type is not selected!");
    return;
  }

  VertexData newData;

  switch (type) {
  case PrimitiveType::Cube:
    newData.VertPos = PrimitivesVerts::cubeVertices;
    newData.VertColors = PrimitivesVerts::cubeColors;
    break;

  default:
    Debug::Error("Undefined mesh (" + name + ") type!");
    return;
  }

  if (buffer) {
    delete buffer;
  }

  buffer = new Buffers(name);

  SetData(newData);

  if (buffer->Upload() != 0) {
    Debug::Error("Mesh (" + name + ") buffer upload failed!");
    return;
  }

  created = true;
}

void LoopEngine::Mesh::DrawAsSolid() {
  if (shader_loaded) {
    UpdateTransform();
    shader->Use();

    shader->SetMat4x4("view", Camera::GetActiveCamera()->GetView());
    shader->SetMat4x4("proj", Camera::GetActiveCamera()->GetProj(window));

    buffer->DrawSolid();
  } else {
    Debug::Error("Mesh(" + name +
                 ") doesn`t have any shader! Continue without drawing.");
    return;
  }
}

void LoopEngine::Mesh::DrawAsLines() { return; }

void LoopEngine::Mesh::UpdateTransform() {
  if (!created) {
    Debug::Warning("Mesh (" + name +
                   ") is not created. Transform wasn't updated");
    return;
  }

  transform.Update();

  shader->SetMat4x4("model", transform.GetMat());
}

// Transform methods init
void LoopEngine::Transform::Update() {
  model = glm::mat4(1.0f);

  model = glm::translate(model, this->GetPosition());

  model = glm::rotate(model, glm::radians(this->GetRotation().x),
                      glm::vec3(1.0f, 0.0f, 0.0f));

  model = glm::rotate(model, glm::radians(this->GetRotation().y),
                      glm::vec3(0.0f, 1.0f, 0.0f));

  model = glm::rotate(model, glm::radians(this->GetRotation().z),
                      glm::vec3(0.0f, 0.0f, 1.0f));

  model = glm::scale(model, this->GetScale());
}
