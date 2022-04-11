#include "gp.h"
#include <fstream>
#include <iostream>


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

void Shader::SetUniform(const std::string& u_name, glm::vec4 value) {

	// Get location of the uniform within the shader program:
	const GLchar* name = u_name.c_str();
	GLint loc = glGetUniformLocation(id, name);
	if (loc == -1)
		throw std::exception("Name of uniform does not correspond with uniform value");

	// Specify the value for the uniform:
	glUniform4fv(loc, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& u_name, GLuint value) {

	// Get location of the uniform within the shader program:
	const GLchar* name = u_name.c_str();
	GLint loc = glGetUniformLocation(id, name);
	if (loc == -1)
		throw std::exception("Name of uniform does not correspond with uniform value");

	// Specify the value for the uniform:
	glUniform1i(loc, value);
}

const GLuint Shader::GetId() {

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
			throw std::exception("Unable to compile vertex shader");
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
			throw std::exception("Unable to compile fragment shader");
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
void Shader::Render(std::shared_ptr<Camera> cam, bool backface_cull) {

	// Render set up:
	glEnable(GL_DEPTH_TEST);
	if (backface_cull) glEnable(GL_CULL_FACE);
	/*glEnable(GL_BLEND);*/
	/*glEnable(GL_ALPHA_TEST);*/
	glViewport(0, 0, (int)cam->size.x, (int)cam->size.y);
	glClearColor(cam->back_col.x * cam->back_col.w, cam->back_col.y * cam->back_col.w, 
		cam->back_col.z * cam->back_col.w, cam->back_col.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	 // Render each mesh:
	for (size_t i = 0; i < meshes.size(); i++)
	{
		// Bind Texture:
		if (meshes[i]->is_wf) glBindTexture(GL_TEXTURE_2D, meshes[i]->GetWfModel().textureId);
		else glBindTexture(GL_TEXTURE_2D, meshes[i]->tex->GetId());
		

		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(GetId());

		// Prepare the model matrix data:
		glm::mat4 model = meshes[i]->GetModelMat();
		glm::vec3 pos = meshes[i]->GetPos();

		// Parse in matrix data from mesh:
		SetUniform("u_Model", model);
		SetUniform("u_View", cam->view);
		SetUniform("u_Projection", cam->proj);
		SetUniform("u_diffColor", meshes[i]->diff_light);

		SetUniform("u_lightPos", glm::vec3(10.0, 0.0f, 0.0f));

		// Bind VAO:
		if (meshes[i]->is_wf) glBindVertexArray(meshes[i]->GetWfModel().vaoId);
		else glBindVertexArray(meshes[i]->vao->GetId());
		

		// Final render:
		if (meshes[i]->is_wf) glDrawArrays(GL_TRIANGLES, 0, meshes[i]->GetWfModel().vertexCount);
		else glDrawArrays(GL_TRIANGLES, 0, meshes[i]->vao->GetVertices());

	}


	if (cam->cubemap && cam->cubemap_obj && cam->cubemap_shader) {

		glDepthFunc(GL_LEQUAL);
		glUseProgram(cam->cubemap_shader->GetId());
		glm::mat4 view = glm::mat4(glm::mat3(cam->GetView()));
		cam->cubemap_shader->SetUniform("u_Projection", cam->GetProj());
		cam->cubemap_shader->SetUniform("u_View", view);
		glBindVertexArray(cam->cubemap_obj->GetId());
		glBindTexture(GL_TEXTURE_CUBE_MAP_SEAMLESS, cam->cubemap->GetId());
		glDrawArrays(GL_TRIANGLES, 0, cam->cubemap_obj->GetVertices());
		glDepthFunc(GL_LESS);
	}

	// Reset the state:
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_DEPTH_TEST);
	if (backface_cull) glDisable(GL_CULL_FACE);
	/*glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);*/
}


// Render the scene using custom framebuffer and shader (for post-processing):
void Shader::Render(std::shared_ptr<Camera> cam, std::shared_ptr<RenderTexture> target,
	bool backface_cull) {

	// Set up rendering for custom framebuffer:
	glBindFramebuffer(GL_FRAMEBUFFER, target->GetId());

	// Render into the custom framebuffer:
	Render(cam, backface_cull);

	// Reset state:
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


void Shader::Swap(std::shared_ptr<RenderTexture> source, std::shared_ptr<RenderTexture> destination,
	GLuint tex_2) {

	// If destination is value, we will render into that framebuffer,
	// If destination is nullptr, we render to the screen:
	if (destination) {
		glBindFramebuffer(GL_FRAMEBUFFER, destination->GetId());
	}

	// Use if the shader takes in two textures:
	if (tex_2) {
		glActiveTexture(GL_TEXTURE0 + 1);
		SetUniform("u_Texture1", 1);
		glBindTexture(GL_TEXTURE_2D, tex_2);
		glActiveTexture(GL_TEXTURE0);
	}

	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(GetId());

	// If destination is valid, render into it's quad,
	// Else we render the source's quad to the screen:
	if (destination) {
		glBindVertexArray(destination->GetVAO()->GetId());
	}
	else {
		glBindVertexArray(source->GetVAO()->GetId());
	}

	// Draw to destination:
	glBindTexture(GL_TEXTURE_2D, source->GetTexId());
	glDrawArrays(GL_TRIANGLES, 0, source->GetVAO()->GetVertices());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}




