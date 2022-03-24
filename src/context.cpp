#include "context.h"
#include "gp.h"
#include <ext.hpp>

// Toggle showing the debug window:
void GpContext::ShowDebugWindow() {
	Debug.RenderWindow();
}

void GpContext::ShowDebugWindow(bool* toggle) {
	if (toggle) { Debug.RenderWindow(); }
}

// Creates a vertex buffer object and returns its ID:
std::shared_ptr<Buffer> GpContext::CreateBuffer() {

	std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
	buffer->context = self.lock();
	GLuint id = 0;
	glGenBuffers(1, &id);
	if (!id)
		throw std::exception("Failed to initialise vertex buffer");
	buffer->id = id;
	std::shared_ptr<int> numb = std::make_shared<int>();
	return buffer;
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
	/*std::shared_ptr<Buffer> buffer = CreateBuffer();*/

	// Add the position data into the buffer:
	for (size_t i = 0; i < positions.size(); i++)
	{
		/*buffer->Add(positions.at(i));*/
	}


}

// Getters:
Debug GpContext::GetDebug() { return Debug; }