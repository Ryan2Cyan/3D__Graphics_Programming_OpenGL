#pragma once
#include <iostream>
#include "GL/glew.h"
#include <vector>

class vbo_obj {
private:
    std::vector<GLfloat> data;
    GLuint size_of_data;
    GLuint id;
    GLsizei num_of_buffers;
    GLenum binding_point;
    GLenum data_usage;

public:
    vbo_obj(std::vector<GLfloat> input_data, GLuint input_size, GLenum input_binding_point, GLenum input_data_usage);

    void generate();
    void bind();
    void unbind();
    void buffer_data();
    GLuint get_size();
    GLuint get_id();
    GLenum get_binding_point();
    std::vector<GLfloat> get_data();
};

