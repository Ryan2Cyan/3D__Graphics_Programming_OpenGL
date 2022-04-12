#pragma once
#include <ext.hpp>
#include <iostream>

struct Rigidbody
{
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
};