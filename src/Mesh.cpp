#include "Mesh.h"
#include "Texture.h"
#include "RenderTexture.h"

// Init mesh via vao and texture:
Mesh::Mesh(std::shared_ptr<VertexArray> vao_arg, std::shared_ptr<Texture> tex_arg, glm::vec3 pos_arg) {

	is_wf = false;
	// Assign values:
	vao = vao_arg;
	tex = tex_arg;
	position = pos_arg;
	diff_light = glm::vec3(1.0, 1.0, 1.0);

	// Create model mat and set initial pos:
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, position);
}

Mesh::Mesh(std::shared_ptr<VertexArray> vao_arg, std::shared_ptr<RenderTexture> rend_tex_arg, glm::vec3 pos_arg) {

	is_wf = false;
	// Assign values:
	vao = vao_arg;
	rend_tex = rend_tex_arg;
	position = pos_arg;
	diff_light = glm::vec3(1.0, 1.0, 1.0);

	// Create model mat and set initial pos:
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, position);
}

// Init mesh via wavefront .obj file:
Mesh::Mesh(std::string filepath, glm::vec3 pos_arg) {

	// Load model from specified filepath:
	is_wf = true;
	const char* p = filepath.c_str();
	if (WfModelLoad(p, &wf_model) != 0) {
		throw std::exception("Could not load model");
	}

	position = pos_arg;
	diff_light = glm::vec3(1.0, 1.0, 1.0);

	// Create model mat and set initial pos:
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, position);
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

GLuint Mesh::GetTexId() {

	if (rend_tex) {
		return rend_tex->GetId();
	}
	return tex->GetId();
}

void Mesh::SetPos(glm::vec3 arg) {
	position = arg;
}

void Mesh::SetDiffuse(glm::vec3 arg) {
	diff_light = arg;
}


