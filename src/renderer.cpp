#include "renderer.hpp"
#include "transform_object.hpp"
#include <print>
#include <vector>

core::Renderer::Renderer(SDL_Window *window) {
    this->init(window);
}

void core::Renderer::init(SDL_Window *window) {
    this->renderer = SDL_CreateRenderer(window, NULL);
    if (renderer != nullptr) was_initialized = true;
}

bool core::Renderer::isInitialized() const {
    return was_initialized;
}

void core::Renderer::destroy() {
    if (renderer) SDL_DestroyRenderer(renderer);
    was_initialized = false;
}

void core::Renderer::render(core::Object &object) {
    auto *d = dynamic_cast<TransformObject*>(&object);
    bool is_transformable = nullptr != d;
    //std::println("Rendered object is {}", (is_transformable ? "TransformObject" : "Object"));
    std::vector<SDL_Vertex> vertices {object.vertex_count};
    for (size_t i = 0; i < object.vertex_count; ++i) {
        auto &current_v = object.vertices[i];
        vertices[i] = {(is_transformable ? d->transform(current_v) : current_v), object.color, current_v};
        //std::println("rendering point at {}, {}", vertices.at(i).position.x, vertices.at(i).position.y);
    }
    SDL_RenderGeometry(renderer, object.texture->get(), vertices.data(), vertices.size(), object.indices, object.index_count);
}

SDL_Renderer *core::Renderer::get() const {
    return renderer;
}

core::Renderer::~Renderer() {
    this->destroy();
}
