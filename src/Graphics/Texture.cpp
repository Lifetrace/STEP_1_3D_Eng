#include "Graphics/Texture.hpp"
#include "Graphics/GLINC.hpp"
#include "Loaders/Png.hpp"

LoopEngine::Texture::Texture(uint id, int width, int height)
    : id(id), width(width), height(height) {}

void LoopEngine::Texture::Bind() { glBindTexture(GL_TEXTURE_2D, id); }

LoopEngine::Texture *LoopEngine::Texture::LoadTexturePNG(std::string filepath) {
  int width, height;
  uint texture_id = Png::LoadPNG(filepath.c_str(), &width, &height);

  if (texture_id == 0) {
    return nullptr;
  }

  TextureList[texture_id] = new Texture(texture_id, width, height);
  return TextureList[texture_id];
}

LoopEngine::Texture::~Texture() { glDeleteTextures(1, &id); }
