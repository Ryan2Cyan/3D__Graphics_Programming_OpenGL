#define SDL_MAIN_HANDLED  
#include "render_loop.h"
#include "sdl_functions.h"
#include "gl_functions.h"
#include "shader_functions.h"
#include <iostream>
#include <SDL.h>
#include <glew.h>

const GLchar* vertex_shader_filepath = "Additional_Files/vertex_shader.txt";

int main(int argc, char* argv[]) {

    // Initialisation (init glew after valid rendering context):
    SDL_Window* window = sdl_init();
    if (glewInit() != GLEW_OK) throw std::exception(); 

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
                         
    std::string vertex_shader_src_str = read_shader_file(vertex_shader_filepath);
    const GLchar* vertex_shader_src_char = vertex_shader_src_str.c_str();  // convert from string to GLchar

    // Create a new vertex shader, attach source code, compile it, and check for errors:
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_src_char, NULL);
    glCompileShader(vertex_shader_id);
    GLint success = 0;
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if(!success) std::cerr << "Could not compile shader  " << vertex_shader_id << std::endl;
   
    // Input Loop:
    sdl_loop(window);


    return 0; // Exit
}