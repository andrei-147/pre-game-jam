#include "app.hpp"
#include <utility>

core::Application::Application(core::ApplicationConfiguration config) : cfg(config) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

template <typename AppLayer>
requires std::derived_from<AppLayer, core::Layer>
void core::Application::addLayer() {
    AppLayer l{};
    layers.push_back(std::move(l));
}

bool core::Application::isRunning() const { return running; }

void core::Application::run() {
    window = SDL_CreateWindow(cfg.name, cfg.dimensions.x, cfg.dimensions.y, 0);
    if (!window) return;
    renderer.init(window);
    if (!renderer.isInitialized()) return;
    for (auto &l : layers)
        l.setRenderer(renderer);
    SDL_Event event;
    uint64_t ns_start = 0;
    while (running) {
        ns_start = SDL_GetTicksNS();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: stop(); break;
                case SDL_EVENT_KEY_DOWN: handleKeyboardInput(event, SDL_EVENT_KEY_DOWN); break;
                case SDL_EVENT_KEY_UP: handleKeyboardInput(event, SDL_EVENT_KEY_UP); break;
            };
        }
        for (auto &l : layers)
            l.update(dt);
        for (auto &l : layers)
            l.render();
        dt = (SDL_GetTicksNS() - ns_start) / 1000.0f;
    }
}

void core::Application::stop() {
    running = false;
}

core::Application::~Application() {
    renderer.destroy();
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
