#pragma once
#include "SDL3/SDL_rect.h"

namespace core {

namespace constants {

inline consteval size_t indices(const size_t size) {
    return (size - 2) * 3;
}

constexpr size_t SQUARE_SIZE = 4;
constexpr SDL_FPoint square_v[SQUARE_SIZE] = {
    {0.0f, 0.0f},
    {1.0f, 0.0f},
    {0.0f, 1.0f},
    {1.0f, 1.0f}
};

constexpr size_t SQUARE_INDICES = indices(SQUARE_SIZE);
constexpr int square_i[SQUARE_INDICES] = {
    0, 1, 2,
    1, 2, 3,
};

constexpr float SINE60 = 0.8660254037844386;
constexpr size_t HEXAGON_SIZE = 6;
constexpr SDL_FPoint hexagon_v[HEXAGON_SIZE] = {
    {0.25f,  0.0f},
    {0.75f,  0.0f},
    {0.00f, -0.5f},
    {1.00f, -0.5f},
    {0.25f, -1.0f},
    {0.75f, -1.0f}
};

constexpr size_t HEXAGON_INDICES = indices(HEXAGON_SIZE);
constexpr int hexagon_i[HEXAGON_INDICES] = {
    0, 1, 2,
    1, 2, 3,
    2, 3, 4,
    3, 4, 5,
};

}

}
