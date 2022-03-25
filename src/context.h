#pragma once
#include "VertexArray.h"
#include <memory>
#include <GL/glew.h>


struct Buffer;
struct VertexArray;
struct Shader;

struct  GpContext
{
	// Utility functions:
	std::shared_ptr<VertexArray> CreateTriangle();

	// Create object functions:
	std::shared_ptr<Buffer> CreateBuffer(); 
	std::shared_ptr<VertexArray> CreateVertexArray();
	std::shared_ptr<Shader> CreateShader(std::string vert_path, std::string frag_path);

	std::weak_ptr<GpContext> self;

private:
	bool show_debug_window = true;
};