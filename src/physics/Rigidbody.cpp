#include "Rigidbody.h"

Rigidbody::Rigidbody() {
	has_collided = false;
	has_stopped = false;
	apply_gravity = true;
	gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	force = glm::vec3(0.0f, 0.0f, 0.0f);
	mass = 10.0f;
}

void Rigidbody::AddForce(glm::vec3 arg) {
	force += arg;
}

void Rigidbody::AddTorque(glm::vec3 arg) {
	torque += arg;
}