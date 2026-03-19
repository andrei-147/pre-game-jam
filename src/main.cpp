#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

constexpr size_t WIREFRAMES = 10;
constexpr size_t VERTICES = 6;
constexpr float SINE = 0.866025403784f;
constexpr float SCALE = 4;

constexpr sf::Vector2f w[WIREFRAMES] = {
    { -0.5f / SCALE, -SINE / SCALE}, // 5
    {  0.5f / SCALE, -SINE / SCALE}, // 6
    {  1.0f / SCALE,  0.0f / SCALE}, // 4
    { -0.5f / SCALE, -SINE / SCALE}, // 5
    { -1.0f / SCALE,  0.0f / SCALE}, // 3
    {  1.0f / SCALE,  0.0f / SCALE}, // 4
    {  0.5f / SCALE,  SINE / SCALE}, // 2
    { -1.0f / SCALE,  0.0f / SCALE}, // 3
    { -0.5f / SCALE,  SINE / SCALE}, // 1
    {  0.5f / SCALE,  SINE / SCALE}, // 2
};

constexpr sf::Vector2f v[VERTICES] = {
    { -0.5f / SCALE,  SINE / SCALE}, // 1
    {  0.5f / SCALE,  SINE / SCALE}, // 2
    { -1.0f / SCALE,  0.0f / SCALE}, // 3
    {  1.0f / SCALE,  0.0f / SCALE}, // 4
    { -0.5f / SCALE, -SINE / SCALE}, // 5
    {  0.5f / SCALE, -SINE / SCALE}, // 6
};

constexpr size_t FPS = 360;
constexpr float DT = 1.0f / FPS;
constexpr sf::Vector2u dim = {1000, 1000};

sf::Vector2f rotate(const sf::Vector2f p, const float theta) {
    float s = std::sin(theta);
    float c = std::cos(theta);
    auto [x, y] = p;
    return {x * c - y * s, x * s + y * c};
}

sf::Vector2f translate(const sf::Vector2f p, const sf::Vector2f off) {
    auto [x, y] = p;
    auto [xf, yf] = off;
    return {x + xf, y + yf};
}

#define px p.x
#define py p.y
#define xf (px + 1.0f) / 2.0f * dim.x
#define yf (1.0f - (py + 1.0f) / 2.0f) * dim.y
sf::Vector2f screen(const sf::Vector2f p) {
    return {xf, yf};
}
#undef xf
#undef yf

int main() {
    sf::RenderWindow win = {sf::VideoMode{dim}, "sfml", sf::Style::Default, sf::State::Windowed};
    win.setFramerateLimit(FPS);

    sf::VertexArray vs;
    sf::Color col = {0, 255, 0, 255};

    bool wireframe = false;

    float theta = 0;
    sf::Vector2f offset = {0.0f, 0.0f};
    float multi = 1.0f;

    while (win.isOpen()) {
        while (const auto &event = win.pollEvent()) {
            if (event->is<sf::Event::Closed>()) win.close();
            if (event->is<sf::Event::KeyPressed>()) {
                auto kcode = event->getIf<sf::Event::KeyPressed>()->code;
                if (kcode == sf::Keyboard::Key::Escape) win.close();
                if (kcode == sf::Keyboard::Key::R) {
                    theta = 0;
                    offset = {0, 0};
                }
                if (kcode == sf::Keyboard::Key::Space) {
                    wireframe = !wireframe;
                }
            }
        }
        multi = 1.0f - (0.5 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift));
        theta += (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) * sf::priv::pi * 2 * DT * multi;
        offset += {
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) * 5.0f * DT * multi,
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) * 5.0f * DT * multi
        };
        win.clear(sf::Color{30, 30, 30, 255});
        const size_t SIZE = wireframe ? WIREFRAMES : VERTICES;
        const sf::Vector2f *a = wireframe ? w : v;
        vs.setPrimitiveType(wireframe ? sf::PrimitiveType::LineStrip : sf::PrimitiveType::TriangleStrip);
        vs.resize(wireframe ? WIREFRAMES : VERTICES);
        vs.clear();
        for (size_t i = 0; i < SIZE; ++i) {
            sf::Vertex tvert = {
                .position = screen(translate(rotate(a[i], theta), offset)),
                .color = col,
                .texCoords = {0.0f, 0.0f}
            };
            vs.append(tvert);
        }
        win.draw(vs);
        win.display();
    }
    return 0;
}
