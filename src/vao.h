#pragma once
#include "GL/glew.h"
#include "vbo.h"

class vao_obj {
private:
    GLuint id;
    const GLsizei num_of_buffers;
    const GLboolean normalize;

public:
    vao_obj(const GLsizei input_num_of_buffers, const GLboolean input_normalize);

    void generate();

    void insert_data(const vbo_obj vertex_buffer, const GLuint input_index);

    void bind(const vbo_obj vertex_buffer) const;

    void unbind(const vbo_obj vertex_buffer) const;

    GLuint get_id() const;
};