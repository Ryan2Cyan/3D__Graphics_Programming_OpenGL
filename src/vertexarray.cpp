#include "VertexArray.h"
#include "Buffer.h"

VertexArray::VertexArray() {
	id = 0;
	dirty = false;
}

// Sends the data contained within each buffer (within the buffers vector), to the GPU:
void VertexArray::SendLayoutData() {

	// Generate VAO:
	if(!id)
		glGenVertexArrays(1, &id);

	if (!id)
		throw std::exception("Failed to initialise vertex array");

	for (size_t i = 0; i < buffers.size(); i++)
	{
		glBindVertexArray(id);
		GLuint buff = buffers[i]->GetId();
		glBindBuffer(GL_ARRAY_BUFFER, buffers[i]->GetId());
		glVertexAttribPointer(i, buffers[i]->GetComponents(), GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	dirty = false;
}

// Add buffer to the buffer vector member:
void VertexArray::AddBuffer(std::shared_ptr<Buffer> buffer_arg) {

	buffers.push_back(buffer_arg); // Add shr_ptr to vector
	dirty = true;
}


const GLuint VertexArray::GetId() {
	if (dirty)
		SendLayoutData();
	return id;
}