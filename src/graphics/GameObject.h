#pragma once
#include <physics/Transform.h>
#include <memory>
#include <vector>
#include <ext.hpp>

struct GpContext;
struct Mesh;


struct GameObject {
	GameObject();
	GameObject(std::shared_ptr<Mesh> mesh);
	GameObject(std::vector<std::shared_ptr<Mesh>> meshes);
	void AddMesh(std::shared_ptr<Mesh> mesh);
	void Translate(glm::vec3 arg);
	void Scale(glm::vec3 arg);
	void Rotate(float angle, glm::vec3 axis);
	const glm::mat4 GetModelMat();
	const glm::vec3 GetPos();
	void SetPos(glm::vec3 arg);
	void SetModelMat(glm::mat4 arg);

private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;
	std::vector<std::shared_ptr<Mesh>> meshes;
	Transform transform;
};