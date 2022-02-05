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

// Change colour of SDL window:
void change_window_colour(GLclampf r, GLclampf g, GLclampf b, GLclampf a, SDL_Window* window)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}