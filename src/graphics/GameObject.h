#pragma once
#include <memory>
#include <vector>
#include <ext.hpp>
#include <physics/Transform.h>
#include <physics/Rigidbody.h>

struct GpContext;
struct Mesh;

struct GameObject {
	GameObject();
	GameObject(std::shared_ptr<Mesh> mesh);
	GameObject(std::vector<std::shared_ptr<Mesh>> meshes);
	void AddMesh(std::shared_ptr<Mesh> mesh);
	void RemoveMesh(std::shared_ptr<Mesh> mesh);
	void AddRigidbody();
	void AddRigidbody(float mass);
	void Translate(glm::vec3 arg);
	void Scale(glm::vec3 arg);
	void Rotate(float angle, glm::vec3 axis);
	const glm::mat4 GetModelMat();
	const std::shared_ptr<Transform> GetTransform();
	const std::shared_ptr<Rigidbody> GetRigidbody();
	void SetPos(glm::vec3 arg);
	void SetModelMat(glm::mat4 arg);

private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::shared_ptr<Rigidbody> rigidBody;
	std::shared_ptr<Transform> transform;

};