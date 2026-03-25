#include "layer.hpp"
#include "renderer.hpp"

void core::Layer::setRenderer(core::Renderer &renderer) {
    this->renderer = &renderer;
}
