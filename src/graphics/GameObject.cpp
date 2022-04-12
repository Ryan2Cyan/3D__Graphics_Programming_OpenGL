#include "GameObject.h"

GameObject::GameObject() {
	transform = std::make_shared<Transform>();
}

GameObject::GameObject(std::shared_ptr<Mesh> mesh) {
	meshes.push_back(mesh);
}

GameObject::GameObject(std::vector<std::shared_ptr<Mesh>> meshes) {
	this->meshes = meshes;
}

void GameObject::AddMesh(std::shared_ptr<Mesh> mesh) {
	meshes.push_back(mesh);
}

// Add component functions:
void GameObject::AddRigidbody() {
	rigidBody = std::make_shared<Rigidbody>();
}

void GameObject::AddRigidbody(float mass) {
	rigidBody = std::make_shared<Rigidbody>();
	rigidBody->mass = mass;
}

void GameObject::Translate(glm::vec3 arg) {
	transform->model = glm::translate(transform->model, arg);
}

void GameObject::Scale(glm::vec3 arg) {
	transform->model = glm::scale(transform->model, arg);
}

void GameObject::Rotate(float angle, glm::vec3 axis) {
	transform->model = glm::rotate(transform->model, glm::radians(angle), axis);
}

const glm::mat4 GameObject::GetModelMat() {
	return transform->model;
}


const std::shared_ptr<Transform> GameObject::GetTransform() {
	return transform;
}

const std::shared_ptr<Rigidbody> GameObject::GetRigidbody() {
	return rigidBody;
}

void GameObject::SetPos(glm::vec3 arg) {
	transform->position = arg;
	transform->model = glm::translate(transform->model, transform->position);
}

void GameObject::SetModelMat(glm::mat4 arg) {
	transform->model = arg;
}