#include "gl_functions.h"

// i) Create a new VBO on the GPU and bind it to GPU.
// ii) Clear the binding point.
// iii) Return new buffer object(s)' ID.
GLuint vbo_set_and_clear(const GLfloat vertices[], const GLsizei num_of_buffers, const GLenum binding_point, const GLenum data_usage) {
    // Create a new VBO on the GPU and bind it
    GLuint vbo_id = 0;
    glGenBuffers(num_of_buffers, &vbo_id);
    if (!vbo_id) throw std::exception();
    glBindBuffer(binding_point, vbo_id);
    glBufferData(binding_point, sizeof(vertices), vertices, data_usage);
    // Clear the buffer object and return ID:
    glBindBuffer(binding_point, 0);
    return vbo_id;
}

// i) Create a new VAO on the GPU and bind it to GPU.
// ii) Assign layout of data (for VBO) to the VAO.
// iii) Return new VAO's ID.
GLuint vao_set_and_clear(const GLfloat vertices[], GLuint vbo_id, const GLsizei num_of_buffers, const GLenum binding_point,
    const GLboolean normalise) {
    // Create a VAO with data from the VBO:
    GLuint vao_id = 0;            
    GLsizei number_of_vertices = (sizeof(vertices) / sizeof(GLfloat)) / 3;
    glGenVertexArrays(num_of_buffers, &vao_id);
    if (!vao_id) throw std::exception();
    glBindVertexArray(vao_id);
    glBindBuffer(binding_point, vbo_id);      
    glVertexAttribPointer(
        0,
        number_of_vertices,
        GL_FLOAT,
        normalise,
        number_of_vertices * sizeof(GLfloat),
        (void*)0);
    glBindBuffer(binding_point, 0);                    // Reset vertex buffer
    glBindVertexArray(0);                              // Reset vertex array
    return vao_id;
}