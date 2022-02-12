#include "program.h"


/////////// CONSTRUCTOR ///////////
program_obj::program_obj() : index_vertex{0}, index_fragment{1}, id{0} {}

/////////// UTILITY ///////////
void program_obj::generate() {
	id = glCreateProgram(); 
}
void program_obj::attach_shaders(GLuint vertex_id, GLuint fragment_id) {
	glAttachShader(id, vertex_id);
	glAttachShader(id, fragment_id);
}
void program_obj::bind_vertex_attribute(const GLchar* attribute_name) {
	glBindAttribLocation(id, index_vertex, attribute_name);
}
void program_obj::bind_fragment_attribute(const GLchar* attribute_name) {
	glBindAttribLocation(id, index_fragment, attribute_name);
}
void program_obj::link() {
	glLinkProgram(id);
	GLint success = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &success); // Check for link failure
	if (!success) throw std::exception();
}
void program_obj::delete_shaders(GLuint vertex_id, GLuint fragment_id) {
	glDetachShader(id, vertex_id);
	glDeleteShader(vertex_id);
	glDetachShader(id, fragment_id);
	glDeleteShader(fragment_id);
}


/////////// GETTERS ///////////
GLuint program_obj::get_id() { return id; }
