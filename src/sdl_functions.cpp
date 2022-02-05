#include "sdl_functions.h"


// Initialisation of SDL and OpenGL context:
SDL_Window* sdl_init() {
    SDL_Window* window = SDL_CreateWindow(  // Create a window:
        "Triangle",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!SDL_GL_CreateContext(window)) throw std::exception(); // Init OpenGL context
    return window;
}
