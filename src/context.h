#pragma once
#include "VertexArray.h"
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>


struct Buffer;
struct VertexArray;
struct Shader;

struct  GpContext
{
	// Utility functions:
	std::shared_ptr<VertexArray> CreateTriangle(const glm::vec3* v_1, const glm::vec3* v_2,
		const glm::vec3* v_3);

	// Create object functions:
	std::shared_ptr<Buffer> CreateBuffer(); 
	std::shared_ptr<VertexArray> CreateVertexArray();
	std::shared_ptr<Shader> CreateShader(std::string vert_path, std::string frag_path);

	std::weak_ptr<GpContext> self;

private:
	bool show_debug_window = true;
};