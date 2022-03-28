#include "gp.h"
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

Shader::~Shader() {
	GLuint del_id = id;
	glDeleteProgram(del_id);
}

// Adds mesh to shader vector - all meshes within this vector will be rendered in loop:
void Shader::AddMeshToRender(std::shared_ptr<Mesh> arg) {
	meshes.push_back(arg);
}

void Shader::SetUniform(const std::string& u_name, glm::mat4 value) {

	// Get location of the uniform within the shader program:
	const GLchar* name = u_name.c_str();
	GLint loc = glGetUniformLocation(id, name);
	if (loc == -1)
		throw std::exception("Name of uniform does not correspond with uniform value");

	// Specify the value for the uniform:
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& u_name, glm::vec3 value) {

	// Get location of the uniform within the shader program:
	const GLchar* name = u_name.c_str();
	GLint loc = glGetUniformLocation(id, name);
	if (loc == -1)
		throw std::exception("Name of uniform does not correspond with uniform value");

	// Specify the value for the uniform:
	glUniform3fv(loc, 1, glm::value_ptr(value));
}

//void Shader::AddSampler(const std::shared_ptr<Sampler> arg) {
//	samplers.push_back(arg);
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

// Render the scene using default framebuffer:
void Shader::Render(glm::ivec2 window_size, glm::vec4 background_col, bool backface_cull, float& angle) {

	// Render set up:
	glEnable(GL_DEPTH_TEST);
	if (backface_cull) glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, window_size.x, window_size.y);
	glClearColor(background_col.x * background_col.w, background_col.y * background_col.w, background_col.z * background_col.w, background_col.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render each mesh in 'meshes' vector:
	 // Render each mesh:
	for (size_t i = 0; i < meshes.size(); i++)
	{

		glBindTexture(GL_TEXTURE_2D, meshes[i]->GetWfModel().textureId);

		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(GetId());

		// Prepare the model matrix
		glm::mat4 model = meshes[i]->GetModelMat();
		glm::vec3 pos = meshes[i]->GetPos();
		model = glm::translate(model, pos);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

		// Increase the float angle so next frame the triangle rotates further
		angle += 1.0f;

		// Parse in matrix data:
		SetUniform("u_Model", model);

		// Render Model:
		glBindVertexArray(meshes[i]->GetWfModel().vaoId);
		glDrawArrays(GL_TRIANGLES, 0, meshes[i]->GetWfModel().vertexCount);

	}

	// Reset the state:
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_BLEND);
	if (backface_cull) glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}


// Render the scene using custom framebuffer and shader (for post-processing):
void Shader::Render(std::shared_ptr<RenderTexture> target, std::shared_ptr<Shader> framebuffer_shader,
	std::shared_ptr<VertexArray> quad, glm::ivec2 window_size, glm::vec4 background_col, bool backface_cull, float& angle) {

	// Set up rendering for custom framebuffer:
	glBindFramebuffer(GL_FRAMEBUFFER, target->GetId());
	glEnable(GL_DEPTH_TEST);
	glClearColor(background_col.x * background_col.w, background_col.y * background_col.w, background_col.z * background_col.w, background_col.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render into the custom framebuffer:
	Render(window_size, background_col, backface_cull, angle);

	// Set up rendering for default framebuffer:
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(background_col.x * background_col.w, background_col.y * background_col.w, background_col.z * background_col.w, background_col.w);
	glClear(GL_COLOR_BUFFER_BIT);

	// Render the framebuffer to the screen:
	glUseProgram(framebuffer_shader->GetId());
	glBindVertexArray(quad->GetId());
	glBindTexture(GL_TEXTURE_2D, target->id);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}