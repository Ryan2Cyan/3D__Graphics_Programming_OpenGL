#include "Gp.h"
#include <iostream>


// Utility functions:
// Creates a 2D triangle - three vertices can be passed in:
std::shared_ptr<VertexArray> GpContext::CreateTriangle() {

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

// Creates a 2D image VAO - filepath to the image can be passed in:
std::shared_ptr<VertexArray> GpContext::Create2DImage(std::string filepath) {

	// Create positions buffer:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();
	glm::vec3 vert_0 = { -0.5f, 0.5f, 0.0f };
	glm::vec3 vert_1 = { -0.5f, -0.5f, 0.0f };
	glm::vec3 vert_2 = { 0.5f, -0.5f, 0.0f };
	glm::vec3 vert_3 = { 0.5f, -0.5f, 0.0f };
	glm::vec3 vert_4 = { 0.5f, 0.5f, 0.0f };
	glm::vec3 vert_5 = { -0.5f, 0.5f, 0.0f };
	pos_buffer->Add(vert_0);
	pos_buffer->Add(vert_1);
	pos_buffer->Add(vert_2);
	pos_buffer->Add(vert_3);
	pos_buffer->Add(vert_4);
	pos_buffer->Add(vert_5);

	// Create texture coords buffer:
	std::shared_ptr<Buffer> tex_buffer = CreateBuffer();
	glm::vec2 tex_0 = { 0.0f, 0.0f };
	glm::vec2 tex_1 = { 0.0f, 1.0f };
	glm::vec2 tex_2 = { 1.0f, 1.0f };
	glm::vec2 tex_3 = { 1.0f, 1.0f };
	glm::vec2 tex_4 = { 1.0f, 0.0f };
	glm::vec2 tex_5 = { 0.0f, 0.0f };
	tex_buffer->Add(tex_0);
	tex_buffer->Add(tex_1);
	tex_buffer->Add(tex_2);
	tex_buffer->Add(tex_3);
	tex_buffer->Add(tex_4);
	tex_buffer->Add(tex_5);

	// Create vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();
	vertex_array->AddBuffer(pos_buffer);
	vertex_array->AddBuffer(tex_buffer);

	return vertex_array;
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



