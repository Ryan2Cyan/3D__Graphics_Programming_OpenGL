#pragma once
#include <ext.hpp>
#include <iostream>

struct Rigidbody
{
	Rigidbody();
	void AddForce(glm::vec3 arg);
	
	bool has_collided;
	bool apply_gravity;
	glm::vec3 gravity;
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
};