#pragma once

#include "SDL3/SDL_render.h"
namespace core {

class Texture {

private:
    SDL_Texture *texture = nullptr;

public:
    /// \brief The Texture constructor for an image texture
    /// \param image_name The name of the image file including extension
    Texture(const char *image_name);

    /// \brief The Texture constructor for a font texture
    /// \param font_name The name of the ttf file including extension
    /// \param size The size to display the font
    Texture(const char *font_name, const size_t size);

    [[nodiscard]] SDL_Texture *get();
};

}
