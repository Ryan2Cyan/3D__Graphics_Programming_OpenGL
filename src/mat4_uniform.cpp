#include "mat4_uniform.h"


/////////// CONSTRUCTOR ///////////
mat4_uniform::mat4_uniform(const GLchar* input_name, const GLsizei input_count, const GLboolean input_transpose) :
	name{ input_name }, value{1.0f}, count{input_count}, transpose{input_transpose}
{
	location = 0;
}

/////////// UTILITY ///////////
void mat4_uniform::translate(const glm::vec3 input_translation) {
	value = glm::translate(value, input_translation);
}
void mat4_uniform::rotate(const GLfloat input_angle, const glm::vec3 input_axis) {
	value = glm::rotate(value, glm::radians(input_angle), input_axis);
}
void mat4_uniform::scale(const glm::vec3 input_scale) {
	value = glm::scale(value, glm::vec3(100, 100, 1));
}
void mat4_uniform::upload_data() {
	glUniformMatrix4fv(location, count, transpose, glm::value_ptr(value));
}

/////////// SETTERS ///////////
void mat4_uniform::set_location(const GLuint program_id) {  // Find and assign uniform location
	location = glGetUniformLocation(program_id, name);
}
void mat4_uniform::set_value(const glm::mat4 input_value) {
	value = input_value;
}

/////////// GETTERS ///////////
glm::mat4 mat4_uniform::get_value() { return value; }
