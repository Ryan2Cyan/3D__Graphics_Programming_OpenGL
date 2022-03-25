#pragma once
#include "buffer.h"
#include "vertexarray.h"
#include <memory>
#include <GL/glew.h>


struct Buffer;
struct VertexArray;

struct  GpContext
{

	// Utility functions:
	void RenderTriangle();

	// Create object functions:
	std::shared_ptr<Buffer> CreateBuffer(); 
	std::shared_ptr<VertexArray> CreateVertexArray();

	std::weak_ptr<GpContext> self;

private:
	bool show_debug_window = true;
};