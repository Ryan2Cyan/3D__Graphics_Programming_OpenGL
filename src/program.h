#pragma once
#include "GL/glew.h"

class program_obj {
private:
	GLuint id;
	GLuint index_vertex;
	GLuint index_fragment;

public:
	/////////// CONSTRUCTOR ///////////
	program_obj();

	/////////// UTILITY ///////////
	void generate();
	void attach_shaders(const GLuint vertex_id, const GLuint fragment_id);
	void bind_vertex_attribute(const GLchar* attribute_name);
	void bind_fragment_attribute(const GLchar* attribute_name);
	void link();
	void delete_shaders(GLuint vertex_id, GLuint fragment_id);

	/////////// GETTERS ///////////
	GLuint get_id() const;

};