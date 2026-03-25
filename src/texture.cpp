#include "texture.hpp"

core::Texture::Texture(const char *image_name) {}

core::Texture::Texture(const char *font_name, size_t font_size) {}

[[nodiscard]] SDL_Texture *core::Texture::get() const {
    return texture;
}

core::Texture::~Texture() {}
