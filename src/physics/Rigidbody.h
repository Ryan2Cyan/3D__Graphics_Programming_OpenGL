#pragma once
#include <ext.hpp>
#include <iostream>

struct Rigidbody
{
	Rigidbody();
	void AddForce(glm::vec3 arg);
	void AddTorque(glm::vec3 arg);

	
	bool has_collided;
	bool apply_gravity;
	glm::vec3 gravity;
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
	glm::vec3 torque;
	glm::vec3 angular_velocity;
	glm::vec3 angular_momentum;
	glm::mat3 interia_tensor_inverse;
	glm::mat3 rotation;
	glm::mat3 body_inertia_tensor_inverse;
	glm::quat rotation_quaterion;
	bool has_stopped;
};