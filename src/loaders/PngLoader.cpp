#include "Graphics/GLINC.hpp"
#include "Graphics/Texture.hpp"
#include "Loaders/Png.hpp"
#include "Other/Debug.hpp"

#include <cstdio>
#include <cstdlib>
#include <png.h>
#include <string>

uint LoopEngine::Png::LoadPNG(const char *file, int *width, int *height) {
  FILE *f;
  int is_png, bit_depth, color_type, row_bytes;
  png_infop info_ptr, end_info;
  png_uint_32 t_width, t_height;
  png_byte header[8], *image_data;
  png_bytepp row_pointers;
  png_structp png_ptr;
  GLuint texture = 0;
  int alpha;

  Debug::Log("Loading PNG: " + std::string(file));

  f = fopen(file, "rb");
  if (!f) {
    Debug::Error("Failed to open PNG file: " + std::string(file));
    return 0;
  }

  if (fread(header, 1, 8, f) != 8) {
    Debug::Error("Failed to read PNG header: " + std::string(file));
    fclose(f);
    return 0;
  }

  is_png = !png_sig_cmp(header, 0, 8);
  if (!is_png) {
    Debug::Error("File is not a valid PNG: " + std::string(file));
    fclose(f);
    return 0;
  }

  Debug::Log("PNG signature is valid");

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    Debug::Error("Failed to create PNG read struct");
    fclose(f);
    return 0;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    Debug::Error("Failed to create PNG info struct");
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(f);
    return 0;
  }

  end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    Debug::Error("Failed to create PNG end info struct");
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(f);
    return 0;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    Debug::Error("libpng error while reading file: " + std::string(file));
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(f);
    return 0;
  }

  png_init_io(png_ptr, f);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  png_get_IHDR(png_ptr, info_ptr, &t_width, &t_height, &bit_depth, &color_type,
               NULL, NULL, NULL);

  *width = t_width;
  *height = t_height;

  Debug::Log("PNG info: " + std::to_string(t_width) + "x" +
             std::to_string(t_height) +
             ", bit depth: " + std::to_string(bit_depth) +
             ", color type: " + std::to_string(color_type));

  png_read_update_info(png_ptr, info_ptr);

  row_bytes = png_get_rowbytes(png_ptr, info_ptr);

  Debug::Log("PNG row bytes: " + std::to_string(row_bytes));

  image_data = (png_bytep)malloc(row_bytes * t_height * sizeof(png_byte));
  if (!image_data) {
    Debug::Error("Failed to allocate PNG image data");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(f);
    return 0;
  }

  row_pointers = (png_bytepp)malloc(t_height * sizeof(png_bytep));
  if (!row_pointers) {
    Debug::Error("Failed to allocate PNG row pointers");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    fclose(f);
    return 0;
  }

  for (unsigned int i = 0; i < t_height; ++i) {
    row_pointers[t_height - 1 - i] = image_data + i * row_bytes;
  }

  Debug::Log("Reading PNG image data");

  png_read_image(png_ptr, row_pointers);

  switch (png_get_color_type(png_ptr, info_ptr)) {
  case PNG_COLOR_TYPE_RGBA:
    alpha = GL_RGBA;
    Debug::Log("PNG color format: RGBA");
    break;

  case PNG_COLOR_TYPE_RGB:
    alpha = GL_RGB;
    Debug::Log("PNG color format: RGB");
    break;

  default:
    Debug::Error("Color type not supported: " +
                 std::to_string(png_get_color_type(png_ptr, info_ptr)));

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(f);
    return 0;
  }

  Debug::Log("Creating OpenGL texture");

  glGenTextures(1, &texture);

  if (texture == 0) {
    Debug::Error("glGenTextures failed");

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(f);
    return 0;
  }

  glBindTexture(GL_TEXTURE_2D, texture);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0, alpha,
               GL_UNSIGNED_BYTE, (GLvoid *)image_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);

  Debug::Log("PNG loaded successfully. Texture ID: " + std::to_string(texture));

  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  free(image_data);
  free(row_pointers);
  fclose(f);

  return texture;
}
