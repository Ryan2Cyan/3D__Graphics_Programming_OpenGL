#include "vbo.h"

/////////// CONSTRUCTOR ///////////
vbo_obj::vbo_obj(GLsizei input_num_of_buffers, std::vector<GLfloat> input_data, GLuint input_size, 
    GLenum input_binding_point, GLenum input_data_usage)
    : num_of_buffers{ input_num_of_buffers }, data {input_data}, binding_point{ input_binding_point }, 
    data_usage{ input_data_usage }, size_of_data{ input_size }
{
    id = 0;
}

/////////// UTILITY ///////////
void vbo_obj::generate() {
    glGenBuffers(num_of_buffers, &id);
    if (!id) throw std::exception();
}
void vbo_obj::bind() const {
    glBindBuffer(binding_point, id);
}
void vbo_obj::unbind() const {
    glBindBuffer(binding_point, 0);
}
void vbo_obj::buffer_data() const {
    glBindBuffer(binding_point, id);
    glBufferData(binding_point, data.size() * sizeof(data.at(0)), &data.at(0), data_usage);
    glBindBuffer(binding_point, 0);
}

/////////// GETTERS ///////////
GLenum vbo_obj::get_binding_point() const { return binding_point; }
GLuint vbo_obj::get_size() const { return size_of_data; }
GLuint vbo_obj::get_id() const { return id; }
std::vector<GLfloat> vbo_obj::get_data() const { return data; };



