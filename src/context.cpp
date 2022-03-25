#include "Context.h"
#include "Shader.h"
#include "Gp.h"
#include <ext.hpp>
#include <iostream>


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

std::shared_ptr<VertexArray> GpContext::CreateTriangle() {

	// Define triangle vertices:
	glm::vec3 vert_1 = { 0.0f, 0.5f, 0.0f };
	glm::vec3 vert_2 = { -0.5f, -0.5f, 0.0f };
	glm::vec3 vert_3 = { 0.5f, -0.5f, 0.0f };

	// Initialise buffer:
	std::shared_ptr<Buffer> pos_buffer = CreateBuffer();
	pos_buffer->Add(glm::vec3(vert_1));
	pos_buffer->Add(glm::vec3(vert_2));
	pos_buffer->Add(glm::vec3(vert_3));

	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

	// Add pos buffer to the vertex array:
	vertex_array->AddBuffer(pos_buffer);

	return vertex_array;
}
