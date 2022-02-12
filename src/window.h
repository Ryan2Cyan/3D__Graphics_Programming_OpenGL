#pragma once
#include <SDL.h>
#include "GL/glew.h"



class sdl_window {
private:
    SDL_Window* window;
    const char* title;
    int x_pos;
    int y_pos;
    int width;
    int height;
    Uint32 flags;

public:
    /////////// CONSTRUCTOR ///////////
    sdl_window(const char* input_title, int input_x, int input_y, int input_w, int input_h, Uint32 input_flags);

    /////////// UTILITY ///////////
    void change_window_colour(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

    /////////// GETTERS ///////////
    SDL_Window* get_window();
    int get_width();
    int get_height();
};