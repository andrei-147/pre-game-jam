#pragma once

#include "renderer.hpp"
namespace core {

class Layer {
protected:
    Renderer *renderer = nullptr;

public:
    /// \brief constructs the layer
    Layer();

    /// \brief Initializes the renderer used by the layer
    /// \param renderer The renderer used by the layer
    void setRenderer(Renderer &renderer);

    /// \brief Updates the entire layer state for the current tick
    /// \param dt The time in milliseconds it took for the last tick to update and render
    virtual void update(float dt) {}

    /// \brief Renders the layer for the current tick
    virtual void render() {}

    virtual ~Layer() = 0;
};

}
