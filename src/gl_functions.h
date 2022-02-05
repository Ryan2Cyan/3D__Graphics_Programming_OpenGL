#pragma once
#include <iostream>
#include <SDL.h>
#include <glew.h>

// i) Create a new VBO on the GPU and bind it to GPU.
// ii) Clear the binding point.
// iii) Return new buffer object(s)' ID.
GLuint vbo_set_and_clear(const GLfloat vertices[], const GLsizei num_of_buffers, const GLenum binding_point, const GLenum data_usage);

// i) Create a new VAO on the GPU and bind it to GPU.
// ii) Assign layout of data (for VBO) to the VAO.
// iii) Return new VAO's ID.
GLuint vao_set_and_clear(const GLfloat vertices[], GLuint vbo_id, const GLsizei num_of_buffers, const GLenum binding_point,
    const GLboolean normalise);