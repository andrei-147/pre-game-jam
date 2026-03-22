#pragma once
#include <vector>

namespace core {

class Renderer {

private:
    bool was_initialized = false;

public:
    /// \brief Initializes the renderer
    /// \param window A window that has already been created
    Renderer();

    /// \brief Used to check if renderer has been initialized
    /// \return true if initialization was successful
    bool isInitialized() const;

    /// \brief The render method that calls the current layer's render method
    void render();

    ~Renderer();
};

}
