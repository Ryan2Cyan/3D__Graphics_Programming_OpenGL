#pragma once
#include <memory>
#include <GL/glew.h>
#include <string>

struct GpContext;

struct Texture {
	Texture(std::string tex_path);
	~Texture();
	const GLuint GetId();


private:
	friend struct GpContext;


	std::shared_ptr<GpContext> context;
	std::string filepath;
	GLuint id;
	bool dirty;
};