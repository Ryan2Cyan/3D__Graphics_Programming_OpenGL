#include "vao.h"

/////////// CONSTRUCTOR ///////////
vao_obj::vao_obj(GLsizei input_num_of_buffers)
    : num_of_buffers{ input_num_of_buffers }
{
    id = 0;
    normalize = GL_FALSE;
}

/////////// UTILITY ///////////
void vao_obj::generate() {  // Create a new VAO on the GPU and bind it to GPU.
    glGenVertexArrays(num_of_buffers, &id);
    if (!id) throw std::exception();
}

void vao_obj::bind(vbo_obj vertex_buffer) {
    glBindVertexArray(id);
    glBindBuffer(vertex_buffer.get_binding_point(), vertex_buffer.get_id());
}

void vao_obj::insert_data(vbo_obj vertex_buffer, GLuint input_index) {  // Assign layout of data (for VBO) to the VAO.
    // Bind:
    glBindVertexArray(id);
    glBindBuffer(vertex_buffer.get_binding_point(), vertex_buffer.get_id());
    // Insert Data:
    glVertexAttribPointer(
        input_index,
        vertex_buffer.get_size(),
        GL_FLOAT,
        normalize,
        vertex_buffer.get_size() * sizeof(GLfloat),
        (void*)0
    );
    glEnableVertexAttribArray(input_index);
    // Unbind:
    glBindVertexArray(0);
    glBindBuffer(vertex_buffer.get_binding_point(), 0);
}

void vao_obj::unbind(vbo_obj vertex_buffer) {
    glBindVertexArray(0);
    glBindBuffer(vertex_buffer.get_binding_point(), 0);
}

/////////// GETTERS ///////////
GLuint vao_obj::get_id() { return id; }