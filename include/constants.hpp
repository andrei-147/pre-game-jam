#pragma once
#include "SDL3/SDL_rect.h"
#include <functional>

namespace core {

namespace constants {

inline std::function<bool(const SDL_FPoint&, const SDL_FPoint&)> point_compare_function =
	[](const SDL_FPoint &a, const SDL_FPoint &b){
		return ((a.x < b.x) && (a.x != b.x)) || ((a.y < b.y) && (a.y != b.y));
	};

inline constexpr float PI = 3.14159265359f;

inline SDL_FPoint screen_dimensions = {1.0f, 1.0f};
inline SDL_FPoint inverse_dimensions = {1.0f, 1.0f};
inline float aspect_ratio = 1.0f;
inline float target_frame_time = 1.0f;

inline consteval size_t indices(const size_t size) {
    return (size - 2) * 3;
}

constexpr size_t SQUARE_VERTICES = 4;
constexpr SDL_FPoint square_v[SQUARE_VERTICES] = {
    {-1.0f, -1.0f}, // 0
    { 1.0f, -1.0f}, // 1
    { 1.0f,  1.0f}, // 2
    {-1.0f,  1.0f}  // 3
};

constexpr size_t SQUARE_INDICES = indices(SQUARE_VERTICES);
constexpr int square_i[SQUARE_INDICES] = {
    0, 1, 2,
    0, 2, 3,
};

constexpr float SINE = 0.8660254037844386;
constexpr size_t HEXAGON_VERTICES = 6;
constexpr SDL_FPoint hexagon_v[HEXAGON_VERTICES] = {
    {-0.5f,  SINE}, // 0
    { 0.5f,  SINE}, // 1
    { 1.0f,  0.0f}, // 2
    { 0.5f, -SINE}, // 3
    {-0.5f, -SINE}, // 4
    {-1.0f,  0.0f}  // 5
};

constexpr size_t HEXAGON_INDICES = indices(HEXAGON_VERTICES);
constexpr int hexagon_i[HEXAGON_INDICES] = {
    0, 1, 5,
    1, 2, 5,
    2, 3, 4,
    2, 4, 5,
};

}

}
