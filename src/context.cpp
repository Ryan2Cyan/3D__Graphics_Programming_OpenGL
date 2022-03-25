#include "context.h"
#include "gp.h"
#include <ext.hpp>
#include <iostream>


// Creates a vertex buffer object and returns its ID:
std::shared_ptr<Buffer> GpContext::CreateBuffer() {

	std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
	buffer->context = self.lock();
	GLuint id = 0;
	glGenBuffers(1, &id);
	if (!id)
		throw std::exception("Failed to initialise vertex buffer");
	buffer->id = id;
	return buffer;
}

// Creates a vertex array and returns its ID:
std::shared_ptr<VertexArray> GpContext::CreateVertexArray() {

	std::shared_ptr<VertexArray> vertex_array = std::make_shared<VertexArray>();
	vertex_array->context = self.lock();
	GLuint id = 0;
	glGenVertexArrays(1, &id);
	if (!id)
		throw std::exception("Failed to initialise vertex array");
	vertex_array->id = id;
	return vertex_array;
}

void GpContext::RenderTriangle() {

	// Define triangle vertices:
	glm::vec3 vert_1 = { 0.0f, 0.5f, 0.0f };
	glm::vec3 vert_2 = { -0.5f, -0.5f, 0.0f };
	glm::vec3 vert_3 = { 0.5f, -0.5f, 0.0f };
	
	// Insert vertex data into a vector:
	std::vector<glm::vec3> positions;
	positions.push_back(vert_1);
	positions.push_back(vert_2);
	positions.push_back(vert_3);

	// Initialise buffer:
	std::shared_ptr<Buffer> buffer = CreateBuffer();

	// Add the position data into the buffer:
	for (size_t i = 0; i < positions.size(); i++)
	{
		buffer->Add(positions.at(i));
	}

	// Initialise vertex array:
	std::shared_ptr<VertexArray> vertex_array = CreateVertexArray();

}
