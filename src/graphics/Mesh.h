#pragma once
#include <memory>
#include <string>
#include <ext.hpp>
#include <wavefront/wavefront.h>

struct GpContext;
struct VertexArray;
struct Texture;
struct Shader;
struct RenderTexture;


struct Mesh {

	Mesh(std::shared_ptr<VertexArray> vao, std::shared_ptr<Texture> tex);
	Mesh(std::string filepath);
	const WfModel GetWfModel();
	const GLuint GetTexId();
	void SetDiffuse(glm::vec3 arg);


private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;

	
	std::shared_ptr<Texture> tex;
	std::shared_ptr<VertexArray> vao;
	WfModel wf_model;
	glm::vec3 diff_light;
	bool is_wf;
};