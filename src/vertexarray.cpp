#include "vertexarray.h"

VertexArray::VertexArray() {
	id = 0;
	dirty = false;
}

const GLuint VertexArray::GetId() {
	return id;
}