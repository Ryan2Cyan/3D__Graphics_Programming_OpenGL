#pragma once
#include "GL/glew.h"
#include "buffer.h"

class vao_obj {
private:
    GLuint id;
    const GLsizei num_of_buffers;
    const GLboolean normalize;

public:
    /////////// CONSTRUCTOR ///////////
    vao_obj(const GLsizei input_num_of_buffers, const GLboolean input_normalize);

    /////////// UTILITY ///////////
    void generate();

    void insert_data(const vbo_obj vertex_buffer, const GLuint input_index, GLuint data_type);

    void bind(const vbo_obj vertex_buffer) const;

    void unbind(const vbo_obj vertex_buffer) const;

    void delete_vao();

    /////////// GETTERS ///////////
    GLuint get_id() const;
};