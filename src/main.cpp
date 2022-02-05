#define SDL_MAIN_HANDLED  
#include "render_loop.h"
#include "sdl_functions.h"
#include "gl_functions.h"
#include <iostream>
#include <SDL.h>
#include <glew.h>



int main(int argc, char* argv[]) {

    // Initialisation:
    SDL_Window* window = sdl_init();
    if (glewInit() != GLEW_OK) throw std::exception();         // Init glew after valid rendering context

    // Define vertices of triangle:
    const GLfloat positions[]{
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    // Bind vertex data to GPU and store the buffer object(s)' ID:
    GLuint triangle_vbo_id = vbo_set_and_clear(positions, 1, GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    // Create a VAO and store layout of VBO:
    GLuint triangle_vao_id = vao_set_and_clear(positions, triangle_vbo_id, 1, GL_ARRAY_BUFFER, GL_FALSE);

    // Input Loop:
    sdl_loop(window);


    return 0; // Exit
}