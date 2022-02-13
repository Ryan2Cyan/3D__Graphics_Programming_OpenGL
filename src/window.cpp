#include "window.h"
#include <iostream>



/////////// CONSTRUCTOR ///////////
sdl_window::sdl_window(const char* input_title, int input_x, int input_y, int input_w, int input_h, Uint32 input_flags) :
    title{ input_title }, x_pos{ input_x }, y_pos{ input_y }, width{ input_w }, height{ input_h }, flags{ input_flags }
{
    window = SDL_CreateWindow(  // Create a window:
        title,
        x_pos,
        y_pos,
        width,
        height,
        flags);
    if (!SDL_GL_CreateContext(window)) throw std::exception(); // Init OpenGL context
}

/////////// UTILITY ///////////
void sdl_window::change_window_colour(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

/////////// GETTERS ///////////
SDL_Window* sdl_window::get_window() const { return window; }
int sdl_window::get_width() const { return width; }
int sdl_window::get_height() const { return height; }
