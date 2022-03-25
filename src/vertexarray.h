#pragma once
#include "context.h"
#include "buffer.h"
#include <GL/glew.h>
#include <vector>
#include <memory>

struct Buffer;

// Buffer Object class:
struct VertexArray
{
	VertexArray();
	const GLuint GetId();

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	GLuint id;
	std::vector<Buffer> buffers; // Each buffer represents an individual attribute
	bool dirty;
};