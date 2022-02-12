#pragma once
#include <vector>
#include "GL/glew.h"
#include "vbo.h"

class vao_obj {
private:
    GLuint id;
    GLsizei num_of_buffers;
    GLboolean normalize;

public:
    vao_obj(GLsizei input_num_of_buffers);

    void generate();

    void bind(vbo_obj vertex_buffer);

    void insert_data(vbo_obj vertex_buffer, GLuint input_index);

    void unbind(vbo_obj vertex_buffer);

    GLuint get_id();
};