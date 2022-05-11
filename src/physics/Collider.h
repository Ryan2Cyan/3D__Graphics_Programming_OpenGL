#pragma once
#include <memory>
#include <ext.hpp>
#include "Transform.h"

// Base/parent collider class, this contains all the functions to test for collisions
// against other colliders:
struct Collider {
	float elasticity;
	glm::vec3 center;
	glm::vec3 prev_center;

	Collider() = default;

	virtual ~Collider() {
		// Virtual destructor to create v-table
	}
};

struct PlaneCollider : Collider {
	glm::vec3 normal;
	float distance;

	PlaneCollider() = default;
};

struct SphereCollider : Collider {
	float radius;

	SphereCollider() = default;
};

