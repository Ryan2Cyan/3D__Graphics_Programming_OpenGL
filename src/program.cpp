#include "program.h"
#include<iostream>

/////////// CONSTRUCTOR ///////////
program_obj::program_obj() : index_vertex{ 0 }, index_fragment{ 1 }, index_texture_coords{ 2 }, id{ 0 } {}

/////////// UTILITY ///////////
void program_obj::generate() {
	id = glCreateProgram(); 
}
void program_obj::attach_shaders(const GLuint vertex_id, const GLuint fragment_id) {
	glAttachShader(id, vertex_id);
	glAttachShader(id, fragment_id);
}
void program_obj::bind_vertex_attribute(const GLchar* attribute_name) {
	glBindAttribLocation(id, index_vertex, attribute_name);
}
void program_obj::bind_fragment_attribute(const GLchar* attribute_name) {
	glBindAttribLocation(id, index_fragment, attribute_name);
}
void program_obj::bind_texture_coords_attribute(const GLchar* attribute_name) {
	glBindAttribLocation(id, index_texture_coords, attribute_name);
}
void program_obj::link() {
	glLinkProgram(id);
	GLint success = 0;
	GLchar infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success); // Check for link failure
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cerr << "Could not compile program object\n Error:" << infoLog << std::endl;
		throw std::exception();
	}
}
void program_obj::delete_shaders(GLuint vertex_id, GLuint fragment_id) {

	glDetachShader(id, vertex_id);
	glDeleteShader(vertex_id);

	glDetachShader(id, fragment_id);
	glDeleteShader(fragment_id);
}

void program_obj::delete_program() {
	glDeleteProgram(id);
}
	

/////////// GETTERS ///////////
GLuint program_obj::get_id() const { return id; }

