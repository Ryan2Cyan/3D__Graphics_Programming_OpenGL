#pragma once
#include <memory>
#include <string>
#include <vector>
#include <ext.hpp>
#include <wavefront/wavefront.h>
#include <GL/glew.h>

struct GpContext;
struct VertexArray;
struct Texture;
struct Shader;


struct Mesh {

	Mesh(std::shared_ptr<VertexArray> vao_arg, std::shared_ptr<Texture> tex_arg, glm::vec3 pos_arg);
	Mesh(std::string filepath, glm::vec3 pos_arg);
	WfModel GetWfModel();
	glm::mat4 GetModelMat();
	glm::vec3 GetPos();
	void SetPos(glm::vec3 arg);

private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;

	std::shared_ptr<Texture> tex;
	std::shared_ptr<VertexArray> vao;
	WfModel wf_model;
	glm::vec3 position;
	glm::mat4 model_mat;
	bool is_wf;
};