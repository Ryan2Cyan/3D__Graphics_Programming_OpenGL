#pragma once
#include <memory>
#include <vector>
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


// CubeMap~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct VertexArray;

struct CubeMap {
	CubeMap(std::vector<std::string> tex_faces);
	~CubeMap();
	const GLuint GetId();


private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	std::shared_ptr<VertexArray> cubemap_obj;
	std::vector<std::string> tex_faces;
	GLuint id;
	bool dirty;
};