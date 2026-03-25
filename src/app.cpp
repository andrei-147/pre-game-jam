#include "app.hpp"
#include "constants.hpp"

core::Application::Application(core::ApplicationConfiguration config) : cfg(config) {
    constants::screen_dimensions.x = cfg.dimensions.x;
    constants::screen_dimensions.y = cfg.dimensions.y;
    constants::inverse_dimensions.x = 1.0f / cfg.dimensions.x;
    constants::inverse_dimensions.y = 1.0f / cfg.dimensions.y;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}


bool core::Application::isRunning() const { return running; }

void core::Application::run() {
    window = SDL_CreateWindow(cfg.name, cfg.dimensions.x, cfg.dimensions.y, 0);
    if (!window) return;
    renderer.init(window);
    if (!renderer.isInitialized()) return;
    for (auto &l : layers)
        l.get()->setRenderer(renderer);
    running = true;
    SDL_Event event;
    uint64_t ns_start = 0;
    while (running) {
        ns_start = SDL_GetTicksNS();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: stop(); break;
                case SDL_EVENT_KEY_DOWN: handleKeyboardInput(event); break;
                case SDL_EVENT_KEY_UP: handleKeyboardInput(event); break;
            };
        }
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(renderer.get());

        for (auto &l : layers)
            l.get()->update(dt);
        for (auto &l : layers)
            l.get()->render();
        dt = (SDL_GetTicksNS() - ns_start) / 1000.0f;
        SDL_RenderPresent(renderer.get());
    }
}

void core::Application::handleKeyboardInput(SDL_Event &event) {
    switch (event.type) {
        case SDL_EVENT_KEY_DOWN: {
            switch (event.key.scancode) {
                case SDL_SCANCODE_ESCAPE: stop();
                default: break;
            }
        } break;
        case SDL_EVENT_KEY_UP: {
        } break;
        default: break;
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
