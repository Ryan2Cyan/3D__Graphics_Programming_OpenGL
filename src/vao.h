#pragma once
#include "GL/glew.h"
#include "vbo.h"

class vao_obj {
private:
    GLuint id;
    const GLsizei num_of_buffers;
    const GLboolean normalize;

public:
    vao_obj(GLsizei input_num_of_buffers, GLboolean input_normalize);

    void generate();

    void insert_data(vbo_obj vertex_buffer, GLuint input_index);

    void bind(vbo_obj vertex_buffer) const;

    void unbind(vbo_obj vertex_buffer) const;

    GLuint get_id() const;
};