#pragma once
#include <functional>
#include "renderer.hpp"

namespace core {

struct ApplicationConfiguration {
    const char *name;
};

class Application {
private:
    ApplicationConfiguration cfg;
    Renderer renderer;
    bool running;

public:
    /// Does NOT create a window on construction
    /// \brief The only costructor of class Application
    /// \param config Specifies the configuration used to start the app
    Application(ApplicationConfiguration config);

    /// The float parameter taken by the function is the delta time of the application
    /// Creates the window when called
    /// \brief Run method should be called only once after setup is done
    /// \param main_loop_logic A void(float) function that is run every game tick
    void run(std::function<void(float)> main_loop_logic);

    /// \brief Stops the application if its running
    void stop();

    /// \brief Check if the application is running
    /// \return true if run was called and window is still open
    bool isRunning() const;
    ~Application() = default;
};

}
