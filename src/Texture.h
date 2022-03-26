#pragma once
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>
#include <string>

struct GpContext;

struct Texture {
	Texture(std::string tex_path);
	GLuint GetId();


private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	std::string filepath;
	GLuint id;
	bool dirty;
};