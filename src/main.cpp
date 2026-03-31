#include "app.hpp"
#include "collision_object.hpp"
#include "constants.hpp"
#include "layer.hpp"
#include "physics_object.hpp"
#include "texture.hpp"
#include <print>

core::ApplicationConfiguration cfg {"sfml", {1280, 720}, 360};
core::Application app {cfg};

class AppLayer : public core::Layer {

private:
    core::Texture text {NULL};
    SDL_FColor col = {0.0f, 1.0f, 0.0f, 1.0f};
    core::CollisionObject obj {
        core::constants::square_v,
        core::constants::SQUARE_VERTICES,
        core::constants::square_i,
        core::constants::SQUARE_INDICES,
        {1.0f, 0.0f, 0.0f, 1.0f},
        text
    };

    core::PhysicsObject player {
        core::constants::hexagon_v,
        core::constants::HEXAGON_VERTICES,
        core::constants::hexagon_i,
        core::constants::HEXAGON_INDICES,
        {0.0f, 1.0f, 0.0f, 1.0f},
        text,
    };

public:
    AppLayer() {
        player.setScaling({.5f, .5f});
        obj.setOffset({0.0f, -core::constants::screen_dimensions.y / 2});
        obj.setScaling({5.0f, 0.2f});
    }

    void onEvent(SDL_Event &event) override {
        switch (event.type) {
            case SDL_EVENT_KEY_DOWN: {
                switch (event.key.scancode) {
                    default: break;
                }
            } break;
        }
    }

    void update(double dt) override {
	auto off = player.getOffset();
	off.x += (app.isKeyPressed(SDL_SCANCODE_D) - app.isKeyPressed(SDL_SCANCODE_A)) * dt * 1000.0f;
	off.y += (app.isKeyPressed(SDL_SCANCODE_W) - app.isKeyPressed(SDL_SCANCODE_S)) * dt * 1000.0f;
	player.setOffset(off);

	auto theta = player.getRotation();
	theta += (app.isKeyPressed(SDL_SCANCODE_LEFT) - app.isKeyPressed(SDL_SCANCODE_RIGHT)) * dt * core::constants::PI * 2.0f;
	player.setRotation(theta);
        std::println("Updating layer! got dt = {} and fps = {}", dt, 1.0 / dt);
	if (player.collides_with(obj)) {
		player.setAcceleration({.0f, .0f});
		player.setVelocity({.0f, .0f});
	} else {
		player.setAcceleration({.0f, -0.05f});
	}
	player.update();
    }

    void render() override {
        renderer->render(player);
        renderer->render(obj);
    }
};

int main() {
    app.addLayer<AppLayer>();
    app.run();
}
