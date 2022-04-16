#pragma once
#include <ext.hpp>
#include <iostream>

struct Rigidbody
{
	void AddForce(glm::vec3 arg);

	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
};