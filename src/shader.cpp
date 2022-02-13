#include "shader.h"
#include <fstream>
#include <iostream>

// Reads contents of a shader txt file:
const std::string read_shader_file(const GLchar* file_path) {
	std::string content;
	std::ifstream file_stream(file_path, std::ios::in);

	// Check if the file can be opened:
	if (!file_stream.is_open()) {
		std::cerr << "Could not read file " << file_path << ". File does not exist." << std::endl;
		return "";
	}
	std::string line = "";
	while (!file_stream.eof()) {    // While the stream has not reached the end of the file
		std::getline(file_stream, line);
		content.append(line + "\n");
	}
	return content;
}

// Generates and compiles a shader from specified src code:
GLuint create_shader_object(const GLenum shader_type, const GLsizei array_count, const GLchar* source_code) {
	GLuint shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, array_count, &source_code, NULL);
	glCompileShader(shader_id);
	GLint success_vert = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success_vert);
	if (!success_vert) {
		std::cerr << "Could not compile shader:  " << shader_id << std::endl;
		return -1;
	}
	return shader_id;
}
