#pragma once
#include "GL/glew.h"
#include "program.h"
#include <ext.hpp>

class mat4_uniform {
private:
	const GLchar* name;
	const GLsizei count;
	const GLboolean transpose;
	GLuint location;
	glm::mat4 value;

public:
	/////////// CONSTRUCTOR ///////////
	mat4_uniform(const GLchar* input_name, const GLsizei input_count, const GLboolean input_transpose);

	/////////// UTILITY ///////////
	void translate(const glm::vec3 input_translation);

	void rotate(const GLfloat input_angle, const glm::vec3 input_axis);

	void scale(const glm::vec3 input_scale);

	void upload_data();

	/////////// SETTERS ///////////
	void set_location(const GLuint program_id);

	void set_value(const glm::mat4 input_value);

	/////////// GETTERS ///////////
	glm::mat4 get_value();
};