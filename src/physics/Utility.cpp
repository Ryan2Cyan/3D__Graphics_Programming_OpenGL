#include "Utility.h"


namespace Pfg
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

	glm::vec3 ImpulseSolver(const float delta_time, const float elasticity, const float object0_mass,
		const float object1_mass, const glm::vec3 object0_vel, const glm::vec3 object1_vel, const glm::vec3 normal) {

		// Calculate angular momentum:
		float angular_mo = (0.0f, 0.0f, 0.0f);
		angular_mo = -(1.0f + elasticity) * glm::dot((object0_vel - object1_vel), normal);
		angular_mo /= (1.0f / object0_mass) + (1.0f / object1_mass);

		return angular_mo * normal / delta_time;

	}

	// Checks if a sphere has clipped into a plane, and returns how much the sphere needs to move to not clip: 
	glm::vec3 SphereToPlaneClipCheck(const glm::vec3 sphere_center0, const float radius, 
		const glm::vec3 plane_center, const glm::vec3 plane_normal, const glm::vec3 collision_point
	) {

		glm::vec3 delta_pos = glm::vec3(0.0f, 0.0f, 0.0f);

		// Calculate how far the sphere (minus the radius) is from the plane:
		float distance = DistanceToPlane(plane_normal, sphere_center0 - radius, plane_center);

		if (distance <= plane_center.y) {
			std::cout << "Sphere Center: " << sphere_center0.y << std::endl;
			std::cout << "Sphere Pos: " << sphere_center0.y + radius << std::endl;
			std::cout << "Plane Pos" << plane_center.y << std::endl;
			std::cout << "Distance" << DistanceToPlane(plane_normal, sphere_center0 + radius, plane_center) << std::endl;
			std::cout << "Clipping" << std::endl;
			std::cout << "Collision Point: " << collision_point.x << ", " << collision_point.y << ", " << collision_point.z << std::endl;
			delta_pos.y -= distance;
		}

		return delta_pos;
	}

}
