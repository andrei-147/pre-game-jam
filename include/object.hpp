#pragma once
#include "texture.hpp"
#include <SDL3/SDL.h>

namespace core {

class Object {

public:
    const SDL_FPoint *vertices;
    const size_t vertex_count;
    const int *indices;
    const size_t index_count;
    const Texture *texture;

    Object() = delete;

    /// \brief Constructor for a generic object
    /// \param vertices A pointer to the first element of an array holding all vertices of the object
    /// \param vertex_count The number of vertices in the array
    /// \param indices A pointer to the first element of an array holding all indices of the object
    /// \param index_count The number of indices in the array
    /// \param texture The texture of the object
    Object(const SDL_FPoint *vertices, const size_t vertex_count, const int *indices, const size_t index_count, const Texture *texture);

    ~Object() = default;
};

}
