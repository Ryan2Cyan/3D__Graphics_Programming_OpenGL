#pragma once
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>
#include <string>


struct Buffer;
struct VertexArray;
struct Shader;
struct Texture;
struct Sampler;

struct  GpContext
{
	// Utility functions:
	std::shared_ptr<VertexArray> CreateTriangle();
	std::shared_ptr<VertexArray> Create2DImage(std::string filepath);

	// Create object functions:
	std::shared_ptr<Buffer> CreateBuffer(); 
	std::shared_ptr<VertexArray> CreateVertexArray();
	std::shared_ptr<Shader> CreateShader(std::string vert_path, std::string frag_path);
	std::shared_ptr<Texture> CreateTexture(std::string tex_path);
	std::shared_ptr<Sampler> CreateSampler();

	std::weak_ptr<GpContext> self;

private:
};