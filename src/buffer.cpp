#include "buffer.h"
#include <iostream>

// Buffer:
Buffer::Buffer() {
	id = 0;
	components = 0;
	type = 0;
	dirty = false;
}

// Sends data contained within the buffer to the GPU:
void Buffer::BufferData() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * data.at(0), &data.at(0), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	dirty = false; 
}

// Add functions will insert data into the buffer:
void Buffer::Buffer::Add(glm::vec2 val) {

	if (type != 0 && type != GL_FLOAT_VEC2) {
		throw std::exception("Buffer type mismatch in buffer.");
	}
	type = GL_FLOAT_VEC2;
	data.push_back(val.x);
	data.push_back(val.y);
	dirty = true;
}

void Buffer::Add(glm::vec3 val) {

	if (type != 0 && type != GL_FLOAT_VEC3) {
		throw std::exception("Buffer type mismatch in buffer.");
	}
	type = GL_FLOAT_VEC3;
	data.push_back(val.x);
	data.push_back(val.y);
	data.push_back(val.z);
	dirty = true;
}

void Buffer::Add(glm::vec4 val) {

	if (type != 0 && type != GL_FLOAT_VEC4) {
		throw std::exception("Buffer type mismatch in buffer.");
	}
	type = GL_FLOAT_VEC4;
	data.push_back(val.x);
	data.push_back(val.y);
	data.push_back(val.z);
	data.push_back(val.w);
	dirty = true;
}

// Return how many components/Attributes are contained in the buffer obj:
const int Buffer::GetComponents() {

	switch (type) {
	case GL_FLOAT_VEC2:
		return data.size() / 2;
		break;
	case GL_FLOAT_VEC3:
		return data.size() / 3;
		break;
	case GL_FLOAT_VEC4:
		return data.size() / 4;
		break;
	default:
		throw std::exception("Buffer type invalid.");
	}
}

// Getter functions:
const int Buffer::GetDataSize() {
	if (data.at(0)) {
		return data.size() * sizeof(data.at(0));
	}
	else {
		throw std::exception("No data in vector - invalid size.");
	}
}

// TODO: Implement GetId func.
const GLuint Buffer::GetId() {
	return id;
}