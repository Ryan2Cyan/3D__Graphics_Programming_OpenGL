#pragma once
#include <ext.hpp>

namespace PFG
{

	float DistanceToPlane(
		const glm::vec3& norm, 
		const glm::vec3& pos0, 
		const glm::vec3& pos1);

	bool MovingSphereToPlaneCollision(const glm::vec3& norm,
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

}
