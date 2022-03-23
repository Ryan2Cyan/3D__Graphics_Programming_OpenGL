#pragma once
#include "GL/glew.h"
#include <vector>
#include <ext.hpp>

// OpenGL Objects:
struct Buffer
{
	Buffer();
	void Add(glm::vec2 val);
	void Add(glm::vec3 val);
	void Add(glm::vec4 val);
	const int GetComponents();
	const int GetDataSize();
	const GLuint GetId();
private:
	GLuint id;
	int components;
	int type;
	std::vector<GLfloat> data;
	bool dirty;
};