#include "GameObject.h"

GameObject::GameObject() {
	transform = std::make_shared<Transform>();
}

GameObject::GameObject(std::shared_ptr<Mesh> mesh) {
	meshes.push_back(mesh);
	transform = std::make_shared<Transform>();
}

GameObject::GameObject(std::vector<std::shared_ptr<Mesh>> meshes) {
	this->meshes = meshes;
}

void GameObject::AddMesh(std::shared_ptr<Mesh> mesh) {
	meshes.push_back(mesh);
}
//
//void GameObject::RemoveMesh(std::shared_ptr<Mesh> mesh) {
//	meshes.erase(std::remove(meshes.begin(), meshes.end(), mesh), meshes.end());
//}

// Add component functions:
void GameObject::AddRigidbody() {
	rigidBody = std::make_shared<Rigidbody>();
}

void GameObject::AddRigidbody(float mass) {

	rigidBody = std::make_shared<Rigidbody>();
	rigidBody->mass = mass;
}

void GameObject::AddRigidbody(float mass, bool apply_gravity) {

	rigidBody = std::make_shared<Rigidbody>();
	rigidBody->mass = mass;
	rigidBody->apply_gravity = apply_gravity;
}

void GameObject::AddRigidbody(float mass, bool apply_gravity, glm::vec3 gravity) {

	rigidBody = std::make_shared<Rigidbody>();
	rigidBody->mass = mass;
	rigidBody->apply_gravity = apply_gravity;
	rigidBody->gravity = gravity;
}

void GameObject::AddSphereCollider(float elasticity, float radius) {

	std::shared_ptr<SphereCollider> temp = std::make_shared<SphereCollider>();
	temp->radius = radius;
	temp->center = transform->position;
	temp->elasticity = elasticity;
	collider = temp;
}

void GameObject::AddPlaneCollider(float elasticity, glm::vec3 normal, float distance) {

	std::shared_ptr<PlaneCollider> temp = std::make_shared<PlaneCollider>();
	temp->normal = normal;
	temp->distance = distance;
	temp->elasticity = elasticity;
	temp->center = transform->position;
	collider = temp;
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

const std::shared_ptr<Collider> GameObject::GetCollider() {
	return collider;
}

void GameObject::SetPos(glm::vec3 arg) {
	transform->position = arg;
	transform->model = glm::translate(transform->model, transform->position);
}

void GameObject::SetModelMat(glm::mat4 arg) {
	transform->model = arg;
}