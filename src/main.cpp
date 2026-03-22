#include <cmath>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <print>
#include <iostream>

constexpr size_t VERTICES = 6;
constexpr size_t WIREFRAMES = (VERTICES - 1) * 2;
constexpr size_t INDICES = 12;
constexpr float SINE = 0.866025403784f;
constexpr float SCALE = 4;
constexpr float PI = 3.14159265359;
constexpr SDL_FColor col = {0.0f, 1.0f, 0.0f, 1.0f};

void operator+=(SDL_FPoint &a, SDL_FPoint b) {
    a.x += b.x;
    a.y += b.y;
}

// constexpr SDL_FPoint v[VERTICES] = {
//     {-1.0f / SCALE,  1.0f / SCALE},
//     { 1.0f / SCALE,  1.0f / SCALE},
//     {-1.0f / SCALE, -1.0f / SCALE},
//     { 1.0f / SCALE, -1.0f / SCALE}
// };

constexpr int i[INDICES] = {
    0, 1, 2,
    1, 2, 3,
    2, 3, 4,
    3, 4, 5
};

constexpr SDL_FPoint v[VERTICES] = {
    { -0.5f / SCALE,  SINE / SCALE}, // 0
    {  0.5f / SCALE,  SINE / SCALE}, // 1
    { -1.0f / SCALE,  0.0f / SCALE}, // 2
    {  1.0f / SCALE,  0.0f / SCALE}, // 3
    { -0.5f / SCALE, -SINE / SCALE}, // 4
    {  0.5f / SCALE, -SINE / SCALE}, // 5
};

constexpr size_t FPS = 360;
constexpr float DT = 1.0f / FPS;
constexpr SDL_FPoint dim = {1000, 1000};

void checkSDL(bool errc) {
    if (errc) std::println(std::cerr, "[SDL] Error: {}", SDL_GetError());
    std::exit(-1);
}

SDL_FPoint rotate(const SDL_FPoint p, const float theta) {
    float s = std::sin(theta);
    float c = std::cos(theta);
    auto [x, y] = p;
    return {x * c - y * s, x * s + y * c};
}

SDL_FPoint translate(const SDL_FPoint p, const SDL_FPoint off) {
    auto [x, y] = p;
    auto [xf, yf] = off;
    return {x + xf, y + yf};
}

#define px p.x
#define py p.y
#define xf (px + 1.0f) / 2.0f * dim.x
#define yf (1.0f - (py + 1.0f) / 2.0f) * dim.y
SDL_FPoint screen(const SDL_FPoint p) {
    return {xf, yf};
}
#undef xf
#undef yf

bool isKeyPressed(size_t scancode) {
    return SDL_GetKeyboardState(NULL)[scancode];
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sfml", dim.x, dim.y, SDL_WINDOW_OPENGL);
    //checkSDL(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    //checkSDL(renderer);

    bool wireframe = false;
    bool running = true;

    float theta = 0;
    SDL_FPoint offset = {0.0f, 0.0f};
    float multi = 1.0f;

    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) goto quit;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                auto scode = event.key.scancode;
                if (scode == SDL_SCANCODE_ESCAPE) goto quit;
                if (scode == SDL_SCANCODE_R) {
                    theta = 0;
                    offset = {0, 0};
                }
                if (scode == SDL_SCANCODE_SPACE) {
                    wireframe = !wireframe;
                }
            }
        }
        multi = 1.0f - (0.5 * isKeyPressed(SDL_SCANCODE_LSHIFT));
        theta += (isKeyPressed(SDL_SCANCODE_LEFT) - isKeyPressed(SDL_SCANCODE_RIGHT)) * PI * 2 * DT * multi;
        offset += {
            (isKeyPressed(SDL_SCANCODE_D) - isKeyPressed(SDL_SCANCODE_A)) * 5.0f * DT * multi,
            (isKeyPressed(SDL_SCANCODE_W) - isKeyPressed(SDL_SCANCODE_S)) * 5.0f * DT * multi
        };
        SDL_Vertex vs[VERTICES];
        SDL_FPoint w[WIREFRAMES];
        size_t len = 0;
        if (!wireframe) {
            for (size_t k = 0; k < VERTICES; ++k) {
                vs[len++] = {screen(translate(rotate(v[k], theta), offset)), col, {0.0f, 0.0f}};
            }
        } else {
            for (size_t k = VERTICES - 1; k > 0; --k) {
                w[len++] = screen(translate(rotate(v[k - 1], theta), offset));
                w[len++] = screen(translate(rotate(v[k], theta), offset));
            }
        }
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColorFloat(renderer, col.r, col.g, col.b, col.a);
        if (!wireframe) SDL_RenderGeometry(renderer, NULL, vs, VERTICES, i, INDICES);
        else SDL_RenderLines(renderer, w, WIREFRAMES);
        SDL_RenderPresent(renderer);

        std::println("theta: {}, offset: {{x: {}, y: {}}}, wireframe: {}", theta, offset.x, offset.y, wireframe);

        frameTime = SDL_GetTicks() - frameStart;
        if (DT * 1000.0f > frameTime) {
            SDL_Delay(DT * 1000.0f - frameTime);
        }
    }
    goto quit;

quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
