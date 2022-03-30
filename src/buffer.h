#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <ext.hpp>

struct GpContext;

// Buffer Object class:
struct Buffer
{
	Buffer();
	~Buffer();
	void BufferData();
	void Add(glm::vec2 val);
	void Add(glm::vec3 val);
	void Add(glm::vec4 val);
	const int GetComponents();
	const int GetDataSize();
	const GLuint GetId();
	const int GetVertices();
private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	GLuint id;
	int type;
	std::vector<GLfloat> data;
	bool dirty;
};