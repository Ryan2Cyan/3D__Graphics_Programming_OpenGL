#pragma once
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>

struct GpContext;
struct Shader;

struct RenderTexture {
	RenderTexture(glm::ivec2 size_arg);
	~RenderTexture();
	void SetSize(glm::ivec2 arg);
	GLuint GetId();
	GLuint GetTexId();
private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;
	glm::ivec2 size;
	GLuint fbo_id;
	GLuint rbo_id;
	GLuint id;
	bool dirty;
};