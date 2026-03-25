#include "app.hpp"
#include "constants.hpp"
#include "layer.hpp"
#include "texture.hpp"
#include "transform_object.hpp"
#include <print>

class AppLayer : public core::Layer {

private:
    core::Texture text {NULL};
    core::TransformObject obj {
        core::constants::square_v,
        core::constants::SQUARE_SIZE,
        core::constants::square_i,
        core::constants::SQUARE_INDICES,
        {0.0f, 1.0f, 0.0f, 1.0f},
        text
    };

public:
    void update(float dt) override {
        std::println("Updating layer! got dt = {}", dt);
        float theta = obj.getRotation();
        obj.setRotation(theta + dt * core::constants::PI * 2);
        obj.setScaling({50.0f, 50.0f});
    }

    void render() override {
        renderer->render(obj);
    }
};

int main() {
    core::ApplicationConfiguration cfg {"sfml", {800, 600}};
    core::Application app {cfg};

    app.addLayer<AppLayer>();
    app.run();
}
