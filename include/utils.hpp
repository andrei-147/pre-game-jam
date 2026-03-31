#pragma once
#include "SDL3/SDL_rect.h"
#include "constants.hpp"
#include <cmath>
#include <print>

namespace core {

namespace utils {

// coords of square are (-0.5, -0.5), (0.5, -0.5), (-0.5, 0.5) and (0.5, 0.5)
// dimensions is the pair of floats describing the dimensions of the screen
// inverse_dimensions is the pair of floats describing 1.0f / the dimensions of the screen
// aspect_ratio is dimensions.y * inverse_dimensions.x
// rendering order is utils::screen(utils::translate(utils::rotate(utils::scale(p, scaling), theta), offset))

inline SDL_FPoint screen(SDL_FPoint p) {
    SDL_FPoint pt {
        (p.x + 1.0f) / 2.0f * constants::screen_dimensions.x,
        (1.0f - (p.y + 1.0f) / 2.0f) * constants::screen_dimensions.y
    };
    //std::println("Screened point: {{{}, {}}} -> {{{}, {}}}", p.x, p.y, pt.x, pt.y);
    return pt;
}

inline SDL_FPoint translate(SDL_FPoint p, SDL_FPoint off) {
    SDL_FPoint pt { p.x + (off.x * constants::inverse_dimensions.x * 2), p.y + (off.y * constants::inverse_dimensions.y * 2) };
    //std::println("Transformed point: {{{}, {}}} -> {{{}, {}}}", p.x, p.y, pt.x, pt.y);
    return pt;
}

inline SDL_FPoint rotate(SDL_FPoint p, float theta) {
    auto [x, y] = p;
    float s = std::sin(theta);
    float c = std::cos(theta);
    SDL_FPoint pt = { x * c - y * s, x * s + y * c };
    //std::println("Rotated point: {{{}, {}}} -> {{{}, {}}}", p.x, p.y, pt.x, pt.y);
    return pt;
}

inline SDL_FPoint scale(SDL_FPoint p, SDL_FPoint scaling) {
    SDL_FPoint pt = { p.x * scaling.x, p.y * scaling.y };
    //std::println("Scaled point: {{{}, {}}} -> {{{}, {}}}", p.x, p.y, pt.x, pt.y);
    return pt;
}

inline SDL_FPoint aspect(SDL_FPoint p, float aspect_ratio) {
    SDL_FPoint pt = { p.x * aspect_ratio, p.y };
    //std::println("Aspected point: {{{}, {}}} -> {{{}, {}}}", p.x, p.y, pt.x, pt.y);
    return pt;
}

}

}
