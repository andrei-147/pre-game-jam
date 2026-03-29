#pragma once
#include "SDL3/SDL_rect.h"

namespace core {

namespace constants {

inline constexpr float PI = 3.14159265359f;

inline SDL_FPoint screen_dimensions = {1.0f, 1.0f};
inline SDL_FPoint inverse_dimensions = {1.0f, 1.0f};
inline float aspect_ratio = 1.0f;

inline consteval size_t indices(const size_t size) {
    return (size - 2) * 3;
}

constexpr size_t SQUARE_VERTICES = 4;
constexpr SDL_FPoint square_v[SQUARE_VERTICES] = {
    {-0.5f, -0.5f},
    { 0.5f, -0.5f},
    {-0.5f,  0.5f},
    { 0.5f,  0.5f}
};

constexpr size_t SQUARE_INDICES = indices(SQUARE_VERTICES);
constexpr int square_i[SQUARE_INDICES] = {
    0, 1, 2,
    1, 2, 3,
};

constexpr float SINE60 = 0.8660254037844386;
constexpr size_t HEXAGON_VERTICES = 6;
constexpr SDL_FPoint hexagon_v[HEXAGON_VERTICES] = {
    {0.25f,  0.0f},
    {0.75f,  0.0f},
    {0.00f, -0.5f},
    {1.00f, -0.5f},
    {0.25f, -1.0f},
    {0.75f, -1.0f}
};

constexpr size_t HEXAGON_INDICES = indices(HEXAGON_VERTICES);
constexpr int hexagon_i[HEXAGON_INDICES] = {
    0, 1, 2,
    1, 2, 3,
    2, 3, 4,
    3, 4, 5,
};

}

}
