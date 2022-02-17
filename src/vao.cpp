#include "vao.h"

/////////// CONSTRUCTOR ///////////
vao_obj::vao_obj(const GLsizei input_num_of_buffers, const GLboolean input_normalize)
    : num_of_buffers{ input_num_of_buffers }, normalize{input_normalize}
{
    id = 0;
}

/////////// UTILITY ///////////
void vao_obj::generate() {  // Create a new VAO on the GPU and bind it to GPU.
    glGenVertexArrays(num_of_buffers, &id);
    if (!id) throw std::exception();
}

void vao_obj::insert_data(const vbo_obj vertex_buffer, const GLuint input_index, GLuint data_type) {  // Assign layout of data (for VBO) to the VAO.
    // Bind:
    glBindVertexArray(id);
    vertex_buffer.bind();
    // Insert Data:
    glVertexAttribPointer(
        input_index,
        vertex_buffer.get_size(),
        data_type,
        normalize,
        vertex_buffer.get_size() * sizeof(data_type),
        (void*)0
    );
    glEnableVertexAttribArray(input_index);
    // Unbind:
    glBindVertexArray(0);
    vertex_buffer.unbind();
}


void vao_obj::bind(const vbo_obj vertex_buffer) const {
    glBindVertexArray(id);
    glBindBuffer(vertex_buffer.get_binding_point(), vertex_buffer.get_id());
}

void vao_obj::unbind(const vbo_obj vertex_buffer) const {
    glBindVertexArray(0);
    glBindBuffer(vertex_buffer.get_binding_point(), 0);
}

void vao_obj::delete_vao() {
    glDeleteVertexArrays(num_of_buffers, &id);
}

/////////// GETTERS ///////////
GLuint vao_obj::get_id() const { return id; }