#pragma once
#include <memory>
#include <string>
#include <vector>
#include <ext.hpp>
#include <wavefront/wavefront.h>
#include <GL/glew.h>

struct GpContext;

struct Mesh {

	Mesh(std::string filepath, glm::vec3 pos_arg);
	WfModel GetWfModel();
	glm::mat4 GetModelMat();
	glm::vec3 GetPos();

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	glm::vec3 position;
	glm::mat4 model_mat;
	WfModel wf_model;
};