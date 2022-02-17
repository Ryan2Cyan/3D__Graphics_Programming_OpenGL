#pragma once
#include "GL/glew.h"

class program_obj {
private:
	GLuint id;
	const GLuint index_vertex;
	const GLuint index_fragment;
	const GLuint index_texture_coords;

public:
	/////////// CONSTRUCTOR ///////////
	program_obj();

	/////////// UTILITY ///////////
	void generate();

	void attach_shaders(const GLuint vertex_id, const GLuint fragment_id);

	void bind_vertex_attribute(const GLchar* attribute_name);

	void bind_fragment_attribute(const GLchar* attribute_name);

	void bind_texture_coords_attribute(const GLchar* attribute_name);

	void link();

	void delete_shaders(GLuint vertex_id, GLuint fragment_id);

	void delete_program();

	/////////// GETTERS ///////////
	GLuint get_id() const;

};