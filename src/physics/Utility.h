#pragma once
#include <ext.hpp>
#include <memory>
#include <graphics/GameObject.h>

namespace Pfg
{
	struct GameObject;

	float DistanceToPlane(
		const glm::vec3& norm, 
		const glm::vec3& pos0, 
		const glm::vec3& pos1);

	bool MovingSphereToPlaneCollision(
		const glm::vec3& norm,
		const glm::vec3& sphere_center0,
		const glm::vec3& sphere_center1, 
		const glm::vec3& plane_center, 
		float radius, 
		glm::vec3& collision_point);

	bool SphereToSphereCollision(
		const glm::vec3& sphere_center0, 
		const glm::vec3 sphere_center1, 
		float radius0,
		float radius1, 
		glm::vec3& collision_point);

	glm::vec3 ImpulseSolver(
		const float delta_time, 
		const float elasticity, 
		const float object0_mass,
		const float object1_mass, 
		const glm::vec3 object0_vel, 
		const glm::vec3 object1_vel, 
		const glm::vec3 normal);

}
