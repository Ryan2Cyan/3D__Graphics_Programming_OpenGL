#pragma once
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>

struct GpContext;
struct VertexArray;
struct Shader;

struct RenderTexture {
	RenderTexture(glm::ivec2 size_arg, std::shared_ptr<VertexArray> quad);
	~RenderTexture();
	void SetSize(glm::ivec2 arg);
	void SetTex(GLuint arg);
	void SetQuad(std::shared_ptr<VertexArray> arg);
	const GLuint GetId();
	const GLuint GetTexId();
	const std::shared_ptr<VertexArray> GetVAO();
	const glm::ivec2 GetSize();
private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;
	glm::ivec2 size;
	GLuint fbo_id;
	GLuint rbo_id;
	GLuint id;
	std::shared_ptr<VertexArray> quad;
	bool dirty;
};