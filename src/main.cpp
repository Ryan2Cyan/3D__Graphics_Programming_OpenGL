#define SDL_MAIN_HANDLED  
#include "render_loop.h"
#include "sdl_functions.h"
#include "vbo.h"
#include "vao.h"
#include "shader_functions.h"
#include <iostream>
#include "SDL.h"
#include "GL/glew.h"
#include <vector>

const GLchar* vertex_shader_filepath = "Additional_Files/vertex_shader.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/fragment_shader.txt";

int main(int argc, char* argv[]) {

    // Initialisation (init glew after valid rendering context):
    SDL_Window* window = sdl_init();
    if (glewInit() != GLEW_OK) throw std::exception(); 

    // Define vertices of triangle:
    std::vector<GLfloat> positions;
    positions.push_back(0.0f);
    positions.push_back(0.5f);
    positions.push_back(0.0f);
    positions.push_back(-0.5f);
    positions.push_back(-0.5f);
    positions.push_back(0.0f);
    positions.push_back(0.5f);
    positions.push_back(-0.5f);
    positions.push_back(0.0f);

    /////////// VERTEX BUFFER OBJECT ///////////
    // Bind vertex data to GPU and store the buffer object(s)' ID:
    vbo_obj buffer_obj(positions, 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    buffer_obj.generate();
    buffer_obj.bind();
    buffer_obj.buffer_data();
    buffer_obj.unbind();


    ///////////// VERTEX ARRAY OBJECT ///////////
    // Create a VAO and store layout of VBO:
    vao_obj vertex_array(1, 0);
    vertex_array.generate();
    vertex_array.bind(buffer_obj);
    vertex_array.insert_data(buffer_obj);
    vertex_array.unbind(buffer_obj);

   

    ///////////// VERTEX SHADER ///////////
    // Vertex Shader: Read source file, then generate and compile shader object:
    std::string vertex_shader_src_str = read_shader_file(vertex_shader_filepath);
    const GLchar* vertex_shader_src_char = vertex_shader_src_str.c_str();  // convert from string to const GLchar*
    GLuint vertex_shader_id = create_shader_object(GL_VERTEX_SHADER, 1, vertex_shader_src_char);
 
   
    ///////////// FRAGMENT SHADER ///////////
    // Fragment Shader: Read source file, then generate and compile shader object:
    std::string fragment_shader_src_str = read_shader_file(fragment_shader_filepath);
    const GLchar* fragment_shader_src_char = fragment_shader_src_str.c_str();  // convert from string to const GLchar*
    GLuint fragment_shader_id = create_shader_object(GL_FRAGMENT_SHADER, 1, fragment_shader_src_char);


    ///////////// SHADER PROGRAM ///////////
    // Create new shader program and attach shader objects:
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glBindAttribLocation(program_id, 0, "in_Position"); // Ensure the VAO "position" attribute stream gets set as the first position
    glLinkProgram(program_id);
    GLint success = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success); // Check for link failure
    if (!success) throw std::exception();
    // Detach and destroy shader objects, as they are no longer needed:
    glDetachShader(program_id, vertex_shader_id);
    glDeleteShader(vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    glDeleteShader(fragment_shader_id);
   

    ///////////// INPUT/RENDER LOOP ///////////
    SDL_Event event;
    bool running = true;

    while (running) {
        change_window_colour(1.0f, 0.0f, 0.0f, 1.0f, window);
       
        glUseProgram(program_id);
        glBindVertexArray(vertex_array.get_id());

        // Draw 3 vertices (a triangle)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Reset the state
        glBindVertexArray(0);
        glUseProgram(0);
        SDL_GL_SwapWindow(window);
        while (SDL_PollEvent(&event) != 0) {  // Check for user input
            switch (event.type)
            {
            case SDL_QUIT:                    // Quit application
                running = false;
                break;
            default:
                break;
            }
        }
    }

    //// Input Loop:
    //sdl_loop(window);
    return 0; // Exit
}