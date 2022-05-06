#include "Utility.h"

namespace PFG
{

	float DistanceToPlane(const glm::vec3& norm, const glm::vec3& pos0, const glm::vec3& pos1) {
		return glm::dot((pos0 - pos1), norm);
	}


	bool MovingSphereToPlaneCollision(const glm::vec3& norm, const glm::vec3& sphere_center0,
		const glm::vec3& sphere_center1, const glm::vec3& plane_center, float radius, glm::vec3& collision_point) {

		float t;

		float d0 = DistanceToPlane(norm, sphere_center0, plane_center);
		float d1 = DistanceToPlane(norm, sphere_center0, plane_center);

		if (glm::abs(d0) <= radius)
		{
			collision_point = sphere_center0;
			t = 0.0f;
			return true;
		}
		if (d0 > radius && d1 < radius)
		{
			t = (d0 - radius) / (d0 - d1);
			collision_point = (1 - t) * sphere_center0 + t * sphere_center1;
			return true;
		}
		return false;
	}

	bool SphereToSphereCollision(const glm::vec3& sphere_center0, const glm::vec3 sphere_center1, float radius0,
		float radius1, glm::vec3& collision_point) {

		float distance = glm::length(sphere_center0 - sphere_center1);
		glm::vec3 norm;

		if (distance <= (radius0 + radius1))
		{
			norm = glm::normalize(sphere_center0 - sphere_center1);
			collision_point = radius0 * norm;
			return true;
		}
		return false;
	}

}
