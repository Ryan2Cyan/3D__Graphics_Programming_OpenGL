#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <string>

struct GpContext;

struct Shader {

	Shader(std::string vert_path, std::string frag_path);
	GLuint GetId();

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	GLuint id;
	bool dirty;
	std::string vert_src;
	std::string frag_src;
};