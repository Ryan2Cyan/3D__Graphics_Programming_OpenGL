#include "vbo.h"

// Default Buffer:

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
    bind();
    glBufferData(binding_point, data.size() * sizeof(data.at(0)), &data.at(0), data_usage);
    unbind();
}

/////////// GETTERS ///////////
GLenum vbo_obj::get_binding_point() const { return binding_point; }
GLuint vbo_obj::get_size() const { return size_of_data; }
GLuint vbo_obj::get_id() const { return id; }
std::vector<GLfloat> vbo_obj::get_data() const { return data; };




// Texture Buffer:

/////////// CONSTRUCTOR ///////////
texture_vbo_obj::texture_vbo_obj(GLsizei input_num_of_buffers, GLenum input_binding_point, GLuint input_level,
    GLint input_internal_format, GLenum input_format, GLenum input_type, GLint input_border,
    unsigned char* input_data, GLsizei input_width, GLsizei input_height)
    : num_of_buffers{ input_num_of_buffers }, binding_point{ input_binding_point }, level{input_level},
    internal_format{input_internal_format}, format{input_format}, type{input_type}, border{input_border},
    data{ input_data }, width{ input_width }, height{input_height}
{
    id = 0;
}
/////////// UTILITY ///////////
void texture_vbo_obj::generate() {
    glGenTextures(num_of_buffers, &id);
    if (!id) throw std::exception();
}
void texture_vbo_obj::bind() const {
    glBindTexture(binding_point, id);
}
void texture_vbo_obj::unbind() const {
    glBindTexture(binding_point, 0);
}
void texture_vbo_obj::buffer_data() const {
    bind();
    glTexImage2D(binding_point, level, internal_format, width, height, border, format, type, data);
    free(data);
    glGenerateMipmap(binding_point);
    unbind();
}



