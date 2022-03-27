#include "Mesh.h"

Mesh::Mesh(std::string filepath, glm::vec3 pos_arg) {

	// Load model from specified filepath:
	const char* p = filepath.c_str();
	if (WfModelLoad(p, &wf_model) != 0) {
		throw std::exception("Could not load model");
	}

	position = pos_arg;
	model_mat = glm::mat4(1.0f);
}


WfModel Mesh::GetWfModel() {
	return wf_model;
}

glm::mat4 Mesh::GetModelMat() {
	return model_mat;
}

glm::vec3 Mesh::GetPos() {
	return position;
}

void Mesh::SetPos(glm::vec3 arg) {
	position = arg;
}


