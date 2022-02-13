#pragma once
#include "GL/glew.h"
#include "program.h"
#include <ext.hpp>

class mat4_uniform {
private:
	GLuint location;
	const GLchar* name;
	glm::mat4 value;
	GLsizei count;
	GLboolean transpose;

public:
	/////////// CONSTRUCTOR ///////////
	mat4_uniform(const GLchar* input_name, GLsizei input_count, GLboolean input_transpose);

	/////////// UTILITY ///////////
	void translate(glm::vec3 input_translation);

	void rotate(GLfloat input_angle, glm::vec3 input_axis);

	void upload_data();

	/////////// SETTERS ///////////
	void set_location(GLuint program_id);

	void set_value(glm::mat4 input_value);
};