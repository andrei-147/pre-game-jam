#include "app.hpp"
#include "constants.hpp"
#include "layer.hpp"
#include "texture.hpp"
#include "transform_object.hpp"
#include <print>

core::ApplicationConfiguration cfg {"sfml", {1280, 720}};
core::Application app {cfg};

class AppLayer : public core::Layer {

private:
    core::Texture text {NULL};
    SDL_FColor col = {0.0f, 1.0f, 0.0f, 1.0f};
    core::TransformObject obj {
        core::constants::square_v,
        core::constants::SQUARE_VERTICES,
        core::constants::square_i,
        core::constants::SQUARE_INDICES,
        col,
        text
    };

    void flipcol() {
        if (col.g > 0) {
            col.g = 0.0f;
            col.r = 1.0f;
        } else {
            col.r = 0.0f;
            col.g = 1.0f;
        }
    }

public:
    AppLayer() {
        obj.setScaling({1.0f, 1.0f});
    }

    void onEvent(SDL_Event &event) override {
        switch (event.type) {
            case SDL_EVENT_KEY_DOWN: {
                switch (event.key.scancode) {
                    case SDL_SCANCODE_SPACE: flipcol(); break;
                    default: break;
                }
            } break;
        }
    }

    void update(float dt) override {
        std::println("Updating layer! got dt = {}", dt);
        obj.color = col;
        float theta = obj.getRotation();
        int dir = app.isKeyPressed(SDL_SCANCODE_LEFT) - app.isKeyPressed(SDL_SCANCODE_RIGHT);
        obj.setRotation(theta + dt * core::constants::PI * 2 * 0.001f * dir);

        auto off = obj.getOffset();
        int dirx = app.isKeyPressed(SDL_SCANCODE_D) - app.isKeyPressed(SDL_SCANCODE_A);
        int diry = app.isKeyPressed(SDL_SCANCODE_W) - app.isKeyPressed(SDL_SCANCODE_S);
        off.x += dirx * dt * 3.0f;
        off.y += diry * dt * 3.0f;
        obj.setOffset(off);
    }

    void render() override {
        renderer->render(obj);
    }
};

int main() {
    app.addLayer<AppLayer>();
    app.run();
}
