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

	Mesh(std::shared_ptr<VertexArray> vao_arg, std::shared_ptr<Texture> tex_arg, glm::vec3 pos_arg);
	Mesh(std::string filepath, glm::vec3 pos_arg);
	const WfModel GetWfModel();
	const glm::mat4 GetModelMat();
	const glm::vec3 GetPos();
	const GLuint GetTexId();
	void SetPos(glm::vec3 arg);
	void SetDiffuse(glm::vec3 arg);

private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;

	
	std::shared_ptr<Texture> tex;
	std::shared_ptr<VertexArray> vao;
	WfModel wf_model;
	glm::vec3 position;
	glm::vec3 diff_light;
	glm::mat4 model_mat;
	bool is_wf;
};