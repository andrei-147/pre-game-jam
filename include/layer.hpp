#pragma once

namespace core {

class Layer {
private:

public:


    /// \brief Updates the entire layer state for the current tick
    virtual void update() {}

    /// \brief Renders the layer for the current tick
    virtual void render() {}
};

}
