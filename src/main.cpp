#define SDL_MAIN_HANDLED  
#include "instance.h"
#include "window.h"
#include "vbo.h"
#include "vao.h"
#include "shader.h"
#include "program.h"
#include "SDL.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <ext.hpp>
#include <iostream>
#include <vector>

const GLchar* vertex_shader_filepath = "Additional_Files/vertex_shader.txt";
const GLchar* fragment_shader_filepath = "Additional_Files/fragment_shader.txt";

int main(int argc, char* argv[]) {

    // Initialisation (init glew after valid rendering context):
    sdl_window window(
        "Triangle OpenGL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );
    
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

    // Define color attributes of triangle:
    std::vector<GLfloat> colors{
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };

    /////////// VERTEX BUFFER OBJECT [POSITIONS] ///////////
    // Bind vertex data to GPU and store the buffer object(s)' ID:
    vbo_obj buffer_obj(positions, 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    buffer_obj.generate();
    buffer_obj.bind();
    buffer_obj.buffer_data();
    buffer_obj.unbind();

    /////////// VERTEX BUFFER OBJECT [COLORS] ///////////
    // Bind vertex data to GPU and store the buffer object(s)' ID:
    vbo_obj color_buffer_obj(colors, 4, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    color_buffer_obj.generate();
    color_buffer_obj.buffer_data();


    ///////////// VERTEX ARRAY OBJECT ///////////
       // Create a VAO and store layout of VBO:
    vao_obj vertex_array(1);
    vertex_array.generate();
    vertex_array.insert_data(buffer_obj, 0);  // Insert position data
    vertex_array.insert_data(color_buffer_obj, 1);  // Insert color data


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
    program_obj program = program_obj();
    program.generate();
    program.attach_shaders(vertex_shader_id, fragment_shader_id);
    program.bind_vertex_attribute("a_position");
    program.bind_fragment_attribute("a_color");
    program.link();
    program.delete_shaders(vertex_shader_id, fragment_shader_id);


    ///////////// SHADER TRANSFORMATIONS ///////////
    // Find uniform locations:
    GLuint model_mat_location = glGetUniformLocation(program.get_id(), "u_model");
    GLuint projection_mat_location = glGetUniformLocation(program.get_id(), "u_projection");

    ///////////// INPUT/RENDER LOOP ///////////
    application application_1(window, program, vertex_array, model_mat_location, projection_mat_location);
    application_1.render_loop();

    return 0; // Exit
}