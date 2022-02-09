#include "vbo.h"


vbo_obj::vbo_obj(std::vector<GLfloat> input_data, GLuint input_size, GLenum input_binding_point, GLenum input_data_usage)
    : data{ input_data }, binding_point{ input_binding_point }, data_usage{ input_data_usage }, size_of_data{input_size}
{
    id = 0;
    num_of_buffers = 1;
}

void vbo_obj::generate() {
    glGenBuffers(num_of_buffers, &id);
    if (!id) throw std::exception();
}
void vbo_obj::bind() {
    glBindBuffer(binding_point, id);
}
void vbo_obj::unbind() {
    glBindBuffer(binding_point, 0);
}
void vbo_obj::buffer_data() {
    glBufferData(binding_point, data.size() * sizeof(data.at(0)), &data.at(0), data_usage);
}

// Getters:
GLenum vbo_obj::get_binding_point() { return binding_point; }
GLuint vbo_obj::get_size() { return size_of_data; }
GLuint vbo_obj::get_id() { return id; }
std::vector<GLfloat> vbo_obj::get_data() { return data; };



