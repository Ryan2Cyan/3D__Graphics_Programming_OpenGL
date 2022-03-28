#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <string>

struct Buffer;
struct GpContext;

// Buffer Object class:
struct VertexArray
{
	VertexArray();
	~VertexArray();
	void SendLayoutData();
	void AddBuffer(std::shared_ptr<Buffer> buffer_arg);
	const GLuint GetId();

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	GLuint id;
	std::vector<std::shared_ptr<Buffer>> buffers; // Each buffer represents an individual attribute
	bool dirty;
};