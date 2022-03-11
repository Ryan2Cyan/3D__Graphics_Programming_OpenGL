#pragma once
#include <iostream>
#include "GL/glew.h"
#include <vector>
#include <ext.hpp>

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


class buffer {
private:
    GLuint id;
    int components;
    std::vector<GLfloat> data;
    bool dirty;
    int type;

public:
    buffer();

    // Destructor: Unbind and delete buffer:
    ~buffer();

    // Add vec2 GLfloat to the buffer:
    void add(glm::vec2 value);

    // Add vec3 GLfloat to the buffer:
    void add(glm::vec3 value);

    // Add vec4 GLfloat to the buffer:
    void add(glm::vec4 value);

    int get_components();

    int get_data_size();

    // Binds buffer, then buffers all the data held within it. Then resets the state:
    GLuint get_id();
};