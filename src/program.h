#pragma once
#include <vector>
#include "GL/glew.h"

class program_obj {
private:
	GLuint id;
	GLuint index_vertex;
	GLuint index_fragment;
	GLuint shader_id_vertex;
	GLuint shader_id_fragment;

public:
	/////////// CONSTRUCTOR ///////////
	program_obj();

	/////////// UTILITY ///////////
	void generate();
	void attach_shaders();
	void bind_vertex_attribute(const GLchar* attribute_name);
	void bind_fragment_attribute(const GLchar* attribute_name);
	void link();
	void delete_vertex(GLuint vertex_id);
	void delete_fragment(GLuint fragment_id);

	/////////// GETTERS ///////////
	GLuint get_id();

};