#include "Shader.h"
#include <fstream>
#include <iostream>


Shader::Shader(std::string vert_path, std::string frag_path) {


	// Load in vertex shader source code:
	std::ifstream my_file;
	std::string line;
	my_file.open(vert_path.c_str());
	if (!my_file.is_open())
		throw std::exception("Unable to open vertex shader source");

	while (!my_file.eof()) {	
		std::getline(my_file, line);
		vert_src += line + "\n";
	}
	my_file.close();

	// Load in fragment shader source code:
	my_file.open(frag_path.c_str());
	if (!my_file.is_open())
		throw std::exception("Unable to open fragment shader source");

	while (!my_file.eof()) {
		std::getline(my_file, line);
		frag_src += line + "\n";
	}
	my_file.close();
	
	id = 0;
	dirty = true;
}

GLuint Shader::GetId() {

	// Create a new vertex shader:
	const char* vert_src = this->vert_src.c_str();
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vert_src, NULL);
	glCompileShader(vertex_shader_id);

	GLint success = 0;
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint max_length = 0;
		glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH,
			&max_length);
		std::vector<GLchar> errorLog(max_length);
		glGetShaderInfoLog(vertex_shader_id, max_length,
			&max_length, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	// Create a new fragment shader:
	const char* frag_src = this->frag_src.c_str();
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &frag_src, NULL);
	glCompileShader(fragment_shader_id);
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint max_length = 0;
		glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH,
			&max_length);
		std::vector<GLchar> errorLog(max_length);
		glGetShaderInfoLog(fragment_shader_id, max_length,
			&max_length, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}
	
	// Create program object:
	id = glCreateProgram();
	glAttachShader(id, vertex_shader_id);
	glAttachShader(id, fragment_shader_id);

	// Attribute streams go here:
	glBindAttribLocation(id, 0, "a_Position");
	glBindAttribLocation(id, 1, "a_TexCoord");
	glBindAttribLocation(id, 2, "a_Normal");

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	glDetachShader(id, vertex_shader_id);
	glDeleteShader(vertex_shader_id);
	glDetachShader(id, fragment_shader_id);
	glDeleteShader(fragment_shader_id);

	dirty = false;
	return id;
}