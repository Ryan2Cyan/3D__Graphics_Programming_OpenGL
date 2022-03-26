#include "Shader.h"
#include "Sampler.h"
#include "Texture.h"
#include "VertexArray.h"
#include <fstream>
#include <iostream>
#include <GL/glew.h>


// Fetch the source codes for the vertex and fragment shaders:
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

void Shader::SetUniform(const std::string& u_name, glm::mat4 value) {

}

void Shader::AddSampler(const std::shared_ptr<Sampler> arg) {
	samplers.push_back(arg);
}

// TODO: Implement render func:
//void Shader::Render(const int w, const int h, glm::vec4 bg_col, std::shared_ptr<VertexArray> vao) {
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glViewport(0, 0, w, h);
//	glClearColor(bg_col.x * bg_col.w, bg_col.y * bg_col.w, bg_col.z * bg_col.w, bg_col.w);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Bind from samplers:
//	//for (size_t t = 0; t < samplers.size(); t++)
//	//{
//	//	glActiveTexture(GL_TEXTURE0 + t);
//	//	glBindTexture(GL_TEXTURE_2D, samplers[0]->GetTexture()->GetId());
//	//	/*glUniform1i(location_of_sampler, active_texture);*/
//	//}
//
//	glBindTexture(GL_TEXTURE_2D, samplers[0]->GetTexture()->GetId());
//
//	// Bind VAO:
//	glBindVertexArray(vao->GetId());
//
//	// Instruct OpenGL to use our shader program and our VAO
//	glUseProgram(id);
//
//	// Draw 6 vertices (a square):
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//
//	// Reset the state:
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glBindVertexArray(0);
//	glUseProgram(0);
//	glDisable(GL_BLEND);
//	glDisable(GL_CULL_FACE);
//	glDisable(GL_DEPTH_TEST);
//}

GLuint Shader::GetId() {

	if (dirty) {
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
	}

	return id;
}