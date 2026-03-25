#pragma once
#include "SDL3/SDL_rect.h"
#include "constants.hpp"
#include <cmath>

namespace core {

namespace utils {

inline SDL_FPoint translate(SDL_FPoint p, SDL_FPoint off) {
    return { p.x + off.x, p.y + off.y };
}

inline SDL_FPoint rotate(SDL_FPoint p, float theta) {
    auto [x, y] = p;
    float s = std::sin(theta);
    float c = std::cos(theta);
    return { x * c - y * s, x * s + y * c };
}

inline SDL_FPoint scale(SDL_FPoint p, SDL_FPoint scaling) {
    return { p.x * scaling.x * constants::inverse_dimensions.x, p.y * scaling.y * constants::inverse_dimensions.y };
}

}

}
