#include "gl_functions.h"

// i) Create a new VBO on the GPU and bind it to GPU.
// ii) Clear the binding point.
// iii) Return new buffer object(s)' ID.
GLuint vbo_set_and_clear(const GLfloat vertices[], const GLsizei num_of_buffers, const GLenum binding_point, const GLenum data_usage) {
    // Create a new VBO on the GPU and bind it
    GLuint positions_vbo_id = 0;
    glGenBuffers(num_of_buffers, &positions_vbo_id);
    if (!positions_vbo_id) throw std::exception();
    glBindBuffer(binding_point, positions_vbo_id);
    glBufferData(binding_point, sizeof(vertices), vertices, data_usage);
    // Clear the buffer object and return ID:
    glBindBuffer(binding_point, 0);
    return positions_vbo_id;
}