#include "Rigidbody.h"


void Rigidbody::AddForce(glm::vec3 arg) {
	force += arg;
}