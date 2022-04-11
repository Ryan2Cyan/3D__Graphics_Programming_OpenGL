#pragma once
#include <ext.hpp>

struct Transform {

	Transform();
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 model;
};