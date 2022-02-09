#pragma once
#include <SDL.h>
#include "GL/glew.h"
#include <iostream>

// Initialisation of SDL and OpenGL context:
SDL_Window* sdl_init();

// Change colour of SDL window:
void change_window_colour(GLclampf r, GLclampf g, GLclampf b, GLclampf a, SDL_Window* window);