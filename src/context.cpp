#include "Gp.h"
#include <iostream>


// Create 2D asset (without texture):
std::shared_ptr<VertexArray> GpContext::Create2D(std::vector<glm::vec3> pos_coords) {

	// Initialise buffer:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();

	// Add pos coords to the buffer:
	for (size_t i = 0; i < pos_coords.size(); i++)
	{
		pos_buffer->Add(pos_coords[i]);
	}
	
	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

	// Add pos buffer to the vertex array:
	vertex_array->AddBuffer(pos_buffer);

	return vertex_array;
}

// Create 2D asset (with texture):
std::shared_ptr<VertexArray> GpContext::Create2D(std::vector<glm::vec3> pos_coords,
	std::vector<glm::vec2> tex_coords) {

	// Initialise buffers:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();
	std::shared_ptr<Buffer> tex_coord_buffer = CreateBuffer();

	// Add pos coords to the buffer:
	if (pos_coords.size() != tex_coords.size())
		throw std::exception("Mismatched attribute vector sizes");
	else {
		for (size_t i = 0; i < pos_coords.size(); i++)
		{
			pos_buffer->Add(pos_coords[i]);
			tex_coord_buffer->Add(tex_coords[i]);
		}
	}

	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

	// Add buffers to the vertex array:
	vertex_array->AddBuffer(pos_buffer);
	vertex_array->AddBuffer(tex_coord_buffer);

	return vertex_array;
}

// Process user input during the input loop:
void GpContext::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Object functions:
// Creates a vertex buffer object and returns its ID:
std::shared_ptr<Buffer> GpContext::CreateBuffer() {

	std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
	buffer->context = self.lock();
	return buffer;
}

std::shared_ptr<VertexArray> GpContext::CreateVertexArray() {

	std::shared_ptr<VertexArray> vertex_array = std::make_shared<VertexArray>();
	vertex_array->context = self.lock();
	return vertex_array;
}

std::shared_ptr<Shader> GpContext::CreateShader(std::string vert_path, std::string frag_path) {

	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert_path, frag_path);
	shader->context = self.lock();
	return shader;
}

std::shared_ptr<Texture> GpContext::CreateTexture(std::string tex_path) {
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(tex_path);
	texture->context = self.lock();
	return texture;
}

//std::shared_ptr<Sampler> GpContext::CreateSampler() {
//	std::shared_ptr<Sampler> sampler = std::make_shared<Sampler>();
//	sampler->context = self.lock();
//	return sampler;
//}
std::shared_ptr<Mesh> GpContext::CreateMesh(std::string filepath, glm::vec3 pos_arg) {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(filepath, pos_arg);
	mesh->context = self.lock();
	return mesh;
}

std::shared_ptr<Mesh> GpContext::CreateMesh(std::shared_ptr<VertexArray> vao_arg,
	std::shared_ptr<Texture> tex_arg, glm::vec3 pos_arg) {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vao_arg, tex_arg, pos_arg);
	mesh->context = self.lock();
	return mesh;
}

std::shared_ptr<Camera> GpContext::CreateCamera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov_arg) {
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(ortho, win_size, position, target, fov_arg);

	camera->context = self.lock();
	return camera;
}

std::shared_ptr<RenderTexture> GpContext::CreateRenderTexture(glm::ivec2 size) {
	std::shared_ptr<RenderTexture> render_texture = std::make_shared<RenderTexture>(size);
	render_texture->context = self.lock();
	return render_texture;
}



