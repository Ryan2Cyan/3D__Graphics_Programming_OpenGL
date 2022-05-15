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

	void ImpulseSolver(
		const float delta_time, 
		const std::shared_ptr<SphereCollider> sphere_col,
		const std::shared_ptr<Rigidbody> sphere_rb, 
		const std::shared_ptr<Rigidbody> plane_rb,
		const glm::vec3 normal);

	glm::vec3 SphereToPlaneClipCheck(
		const glm::vec3 sphere_center0,
		const float radius,
		const glm::vec3 plane_center,
		const glm::vec3 plane_normal,
		const glm::vec3 collision_point
	);

}
