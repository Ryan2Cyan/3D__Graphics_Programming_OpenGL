#pragma once
#include <memory>
#include <ext.hpp>
#include "Transform.h"

enum colliderType
{
	plane, sphere, none
};

// Base/parent collider class, this contains all the functions to test for collisions
// against other colliders:
struct Collider {
	float elasticity;
	colliderType type;
	glm::vec3 center;

	virtual ~Collider() {
		// Virtual destructor to create v-table
	}
};

struct PlaneCollider : Collider {
	glm::vec3 normal;
	float distance;
};

struct SphereCollider : Collider {
	float radius;
};

