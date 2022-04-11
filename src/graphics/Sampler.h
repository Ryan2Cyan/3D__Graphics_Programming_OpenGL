#pragma once
#include <memory>
#include <GL/glew.h>

struct GpContext;
struct Texture;

struct Sampler {
	void Add(const std::shared_ptr<Texture> arg);
	std::shared_ptr<Texture> GetTexture();
	
private:
	friend struct GpContext;
	std::shared_ptr<GpContext> context;
	GLuint id;
	std::shared_ptr<Texture> texture;
};