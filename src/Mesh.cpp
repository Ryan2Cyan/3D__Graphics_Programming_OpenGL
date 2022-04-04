#include "Mesh.h"
#include "Texture.h"
#include "RenderTexture.h"

// Init mesh via vao and texture:
Mesh::Mesh(std::shared_ptr<VertexArray> vao, std::shared_ptr<Texture> tex, glm::vec3 pos) {

	is_wf = false;
	// Assign values:
	this->vao = vao;
	this->tex = tex;
	position = pos;
	diff_light = glm::vec3(1.0, 1.0, 1.0);

	// Create model mat and set initial pos:
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, position);
}

// Init mesh via wavefront .obj file:
Mesh::Mesh(std::string filepath, glm::vec3 pos) {

	// Load model from specified filepath:
	is_wf = true;
	const char* p = filepath.c_str();
	if (WfModelLoad(p, &wf_model) != 0) {
		throw std::exception("Could not load model");
	}

	position = pos;
	diff_light = glm::vec3(1.0, 1.0, 1.0);

	// Create model mat and set initial pos:
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, position);
}


const WfModel Mesh::GetWfModel() {
	return wf_model;
}

const glm::mat4 Mesh::GetModelMat() {
	return model_mat;
}

const glm::vec3 Mesh::GetPos() {
	return position;
}

const GLuint Mesh::GetTexId() {

	return tex->GetId();
}

void Mesh::SetPos(glm::vec3 arg) {
	position = arg;
}

void Mesh::SetDiffuse(glm::vec3 arg) {
	diff_light = arg;
}


