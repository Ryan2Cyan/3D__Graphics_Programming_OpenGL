#include <iostream>
#define SDL_MAIN_HANDLED  
#include <SDL.h>
#include <glew.h>
#include "sdl_loop.h"


int main(int argc, char* argv[]) {

    // Initialisation:
    SDL_Window* window = SDL_CreateWindow(  // Create a window:
        "Triangle",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!SDL_GL_CreateContext(window)) throw std::exception(); // Init OpenGL context
    if (glewInit() != GLEW_OK) throw std::exception();          // Init glew after valid rendering context

    // Define vertices of triangle:
    const GLfloat positions[]{
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };


    // Create a new VBO on the GPU and bind it
    GLuint positionsVboID = 0;                           // Create ID for the VBO                 
    glGenBuffers(1, &positionsVboID);                    // Create a new VBO
    if (!positionsVboID) throw std::exception();         // Check for error
    glBindBuffer(GL_ARRAY_BUFFER, positionsVboID);       // Bind new VBO to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);     // Insert triangle data into the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);                    // Reset the buffer by binding it to nothing

    // Create a VAO with data from the VBO:
    GLuint vaoID = 0;                                    // Create ID for the VBO 
    glGenVertexArrays(1, &vaoID);                        // Create a new VAO
    if (!vaoID) throw std::exception();                  // Check for error
    glBindVertexArray(vaoID);                            // Bind vertex array to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, positionsVboID);       // Bind position vertex buffer to the GPU
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