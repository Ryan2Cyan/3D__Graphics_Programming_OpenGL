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
    GLuint triangle_buffer_id = vbo_set_and_clear(positions, 1, GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    // Create a VAO with data from the VBO:
    GLuint vaoID = 0;                                    // Create ID for the VBO 
    glGenVertexArrays(1, &vaoID);                        // Create a new VAO
    if (!vaoID) throw std::exception();                  // Check for error
    glBindVertexArray(vaoID);                            // Bind vertex array to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer_id);       // Bind position vertex buffer to the GPU
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GLfloat),
        (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);                    // Reset vertex buffer
    glBindVertexArray(0);                                // Reset vertex array


    // Input Loop:
    sdl_loop(window);


    return 0; // Exit
}