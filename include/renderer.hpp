#pragma once
#include <SDL3/SDL.h>

namespace core {

class Renderer {

private:
    bool was_initialized = false;
    SDL_Renderer *renderer = nullptr;

public:
    /// \brief Creates the renderer but does not initialize it
    Renderer();

    /// \brief Initializes the renderer
    /// \param window A window that has already been created
    Renderer(SDL_Window *window);

    /// \brief Initializes the renderer if it hasn't already been initialized
    /// \param window A window that has already been created
    void init(SDL_Window *window);

    /// \brief Used to check if renderer has been initialized
    /// \return true if initialization was successful
    bool isInitialized() const;

    /// \brief The render method that renders an object
    void render();

    /// \brief Safely destroys current renderer
    void destroy();

    ~Renderer();
};

}
