#pragma once
#include <iostream>
#include "GL/glew.h"
#include <vector>

class vbo_obj {
private:
    const std::vector<GLfloat> data;
    const GLuint size_of_data;
    const GLsizei num_of_buffers;
    const GLenum binding_point;
    const GLenum data_usage;
    GLuint id;
   

public:
    vbo_obj(GLsizei input_num_of_buffers, std::vector<GLfloat> input_data, GLuint input_size, GLenum
        input_binding_point, GLenum input_data_usage);


    void generate();
    void bind() const;
    void unbind() const;
    void buffer_data() const;

    GLuint get_size() const;
    GLuint get_id() const;
    GLenum get_binding_point() const;
    std::vector<GLfloat> get_data() const;
};



class texture_vbo_obj {
private:
    GLsizei width;
    GLsizei height;
    const GLuint level;
    const GLint internal_format;
    const GLenum format;
    const GLenum type;
    const GLint border;
    const GLsizei num_of_buffers;
    const GLenum binding_point;
    unsigned char* data;
    GLuint id;
public:
    /////////// CONSTRUCTOR ///////////
    texture_vbo_obj(GLsizei input_num_of_buffers, GLenum input_binding_point, GLuint input_level,
        GLint input_internal_format, GLenum input_format, GLenum input_type, GLint input_border,
        unsigned char* input_data, GLsizei input_width, GLsizei input_height);

    /////////// UTILITY ///////////
    void generate();
    void bind() const;
    void unbind() const;
    void buffer_data() const;
};