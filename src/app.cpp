#include "app.hpp"
#include "constants.hpp"
#include <print>
#include <algorithm>

core::Application::Application(core::ApplicationConfiguration config) : cfg(config) {
    constants::screen_dimensions.x = cfg.dimensions.x;
    constants::screen_dimensions.y = cfg.dimensions.y;
    constants::inverse_dimensions.x = 1.0f / cfg.dimensions.x;
    constants::inverse_dimensions.y = 1.0f / cfg.dimensions.y;
    constants::aspect_ratio = constants::screen_dimensions.y * constants::inverse_dimensions.x;
    constants::target_frame_time = 1.0f / cfg.fps;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}


bool core::Application::isRunning() const { return running; }

bool core::Application::isKeyPressed(const SDL_Scancode scancode) {
    return SDL_GetKeyboardState(NULL)[scancode];
}

void core::Application::run() {
    window = SDL_CreateWindow(cfg.name, cfg.dimensions.x, cfg.dimensions.y, 0);
    if (!window) return;
    renderer.init(window);
    if (!renderer.isInitialized()) return;
    for (auto &l : layers)
        l.get()->setRenderer(renderer);
    running = true;
    SDL_Event event;
    uint64_t start = 0;
    while (running) {
        start = SDL_GetPerformanceCounter();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: stop(); break;
                case SDL_EVENT_KEY_DOWN: handleKeyboardInput(event); break;
                case SDL_EVENT_KEY_UP: handleKeyboardInput(event); break;
            };
            for (auto &ptr : layers) {
                ptr.get()->onEvent(event);
            }
        }
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(renderer.get());

        for (auto &l : layers)
            l.get()->update(dt);
        for (auto &l : layers)
            l.get()->render();
        SDL_RenderPresent(renderer.get());
        dt = (SDL_GetPerformanceCounter() - start) / (float)SDL_GetPerformanceFrequency();
	if (dt < core::constants::target_frame_time) {
		SDL_Delay(std::max(0.0, (core::constants::target_frame_time - dt) * 1000.0f - 2.0f));
		do {
        		dt = (SDL_GetPerformanceCounter() - start) / (float)SDL_GetPerformanceFrequency();
		} while (dt < core::constants::target_frame_time);
	}
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
