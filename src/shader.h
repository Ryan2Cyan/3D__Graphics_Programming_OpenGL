#pragma once
#include <string>
#include "GL/glew.h"

// Reads contents of a shader txt file:
const std::string read_shader_file(const char* file_path);

// Generates and compiles a shader from specified src code:
GLuint create_shader_object(const GLenum shader_type, const GLsizei array_count, const GLchar* source_code);