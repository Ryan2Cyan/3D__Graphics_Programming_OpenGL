#pragma once
#include <ext.hpp>

struct CollisionPoints {
	glm::vec3 pointA; 
	glm::vec3 pointB;
	glm::vec3 norm;
	float depth;
	bool has_collision;
};