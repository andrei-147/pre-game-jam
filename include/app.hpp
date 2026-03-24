#pragma once
#include "layer.hpp"
#include "renderer.hpp"
#include <concepts>
#include <vector>

namespace core {

struct ApplicationConfiguration {
    const char *name;
    SDL_Point dimensions;
};

class Application {
private:
    ApplicationConfiguration cfg; // the application's configuration
    SDL_Window *window = nullptr; // the pointer to the main window
    Renderer renderer; // the renderer wrapper used to render all objects
    bool running; // the flag that tracks whether the application is running or not
    float dt = 1.0f / 60.0f; // the time in milliseconds it took the last frame to update and render
    std::vector<Layer> layers;

    void handleKeyboardInput(SDL_Event &event, SDL_EventType type);

    void cleanup();

public:
    /// Does NOT create a window on construction
    /// \brief The only costructor of class Application
    /// \param config Specifies the configuration used to start the app
    Application(ApplicationConfiguration config);

    template<typename AppLayer>
    requires std::derived_from<AppLayer, Layer>
    void addLayer();

    /// Creates a window and a renderer when called
    /// \brief Run method should be called only once after setup is done
    void run();

    /// \brief Stops the application if its running
    void stop();

    /// \brief Check if the application is running
    /// \return true if run was called and window is still open
    bool isRunning() const;


    ~Application();
};

}
