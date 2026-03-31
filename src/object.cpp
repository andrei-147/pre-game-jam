#include "object.hpp"


core::Object::Object(const SDL_FPoint *vertices, const size_t vertex_count, const int *indices, const size_t index_count, SDL_FColor color, Texture &texture)
: vertices(vertices), vertex_count(vertex_count), indices(indices), index_count(index_count), color(color), texture(&texture) {}
