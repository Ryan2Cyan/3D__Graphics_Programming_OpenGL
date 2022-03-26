#include "Gp.h"
#include <iostream>


// Utility functions:
// Creates a 2D triangle - three vertices can be passed in:
std::shared_ptr<VertexArray> GpContext::CreateTriangle(const glm::vec3* v_1, const glm::vec3* v_2,
	const glm::vec3* v_3) {

	// Initialise buffer:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();
	glm::vec3 vert_1 = { -0.5f, 0.5f, 0.0f };
	glm::vec3 vert_2 = { 0.5f, 0.5f, 0.0f };
	glm::vec3 vert_3 = { 0.5f, -0.5f, 0.0f };
	glm::vec3 vert_4 = { 0.5f, -0.5f, 0.0f };
	glm::vec3 vert_5 = { -0.5f, -0.5f, 0.0f };
	glm::vec3 vert_6 = { -0.5f, 0.5f, 0.0f };
	pos_buffer->Add(vert_1);
	pos_buffer->Add(vert_2);
	pos_buffer->Add(vert_3);
	pos_buffer->Add(vert_4);
	pos_buffer->Add(vert_5);
	pos_buffer->Add(vert_6);

	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

	// Add pos buffer to the vertex array:
	vertex_array->AddBuffer(pos_buffer);

	return vertex_array;
}

// Creates a 2D image - filepath to the image can be passed in:
std::shared_ptr<VertexArray> GpContext::Create2DImage(std::string filepath) {
	return NULL;
}

// Object functions:
// Creates a vertex buffer object and returns its ID:
std::shared_ptr<Buffer> GpContext::CreateBuffer() {

	std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
	buffer->context = self.lock();
	return buffer;
}

// Creates a vertex array and returns its ID:
std::shared_ptr<VertexArray> GpContext::CreateVertexArray() {

	std::shared_ptr<VertexArray> vertex_array = std::make_shared<VertexArray>();
	vertex_array->context = self.lock();
	return vertex_array;
}

// Creates a shader and returns its ID:
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



