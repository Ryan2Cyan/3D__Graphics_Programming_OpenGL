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

	void ImpulseSolver(const float delta_time, const std::shared_ptr<SphereCollider> sphere_col,
		 const std::shared_ptr<Rigidbody> sphere_rb, const std::shared_ptr<Rigidbody> plane_rb, 
		const glm::vec3 normal) {

	
		// Set values:
		float j_linear = 0.0f;
		float j_angular = 0.0f;
		float e = sphere_col->elasticity;
		glm::vec3 r1 = sphere_col->radius * normal;
		float one_over_mass_sphere = 1.0f / sphere_rb->mass;
		float one_over_mass_plane = 1.0f / plane_rb->mass;
		glm::vec3 sphere_vel = sphere_rb->velocity;
		glm::vec3 plane_vel = plane_rb->velocity;
		glm::vec3 relative_vel = sphere_vel - plane_vel;
		glm::vec3 contact_normal = normal;
		/*glm::mat3 inertia_tensor_inverse = sphere_rb->interia_tensor_inverse;*/

		// Calculate linear force:
		j_linear = (glm::dot(-(1.0f + e) * (sphere_vel), contact_normal)) / one_over_mass_sphere + one_over_mass_plane;

		// Calcular angular force:
		/*j_angular = (glm::dot(-(1.0f + e) * (relative_vel), contact_normal)) / (one_over_mass_sphere + one_over_mass_plane 
			+ glm::dot(inertia_tensor_inverse * (r1 * contact_normal), contact_normal));*/

		// Calculate impulse force & contact force:
		glm::vec3 impulse_force = (j_angular + j_linear) * contact_normal;
		glm::vec3 contact_force = -sphere_rb->gravity * sphere_rb->mass;

		// Apply impulse and contact forces:
		sphere_rb->AddForce(impulse_force + contact_force);
		sphere_rb->velocity += (impulse_force / sphere_rb->mass);

		//// Calculate forward relative velocity perpendicular to the contact normal:
		//glm::vec3 forward_relative_velocity = relative_vel - glm::dot(relative_vel, contact_normal) *
		//	contact_normal;

		//// Calculate the forward relative direction, perpendicular to the contact normal:
		//glm::vec3 forward_relative_direction = glm::vec3(0.0f, 0.0f, 0.0f);
		//if (forward_relative_velocity != glm::vec3(0.0f, 0.0f, 0.0f)) {
		//	forward_relative_direction = glm::normalize(forward_relative_velocity);
		//}

		//// Calculate friction:
		//float mu = 0.5f;
		//glm::vec3 friction_direction = forward_relative_velocity * -1.0f;
		//glm::vec3 friction_force = friction_direction * mu * glm::length(contact_force);

		//// Check whether the friction is enough to stop the object:
		//if (glm::length(forward_relative_velocity) - ((glm::length(friction_force) / sphere_rb->mass) *
		//	delta_time) > 0.0f) {
		//	sphere_rb->AddForce(friction_force);
		//}
		//else {
		//	friction_force = forward_relative_velocity * -1.0f;
		//	sphere_rb->AddForce(friction_force);
		//	sphere_rb->has_stopped = true;
		//}

		//// Calculate torque:
		//glm::vec3 temp_torque = (glm::cross(r1, contact_force)) + (glm::cross(r1, friction_force));
		//temp_torque.x -= sphere_rb->angular_momentum.x * 20.0f;
		//temp_torque.z -= sphere_rb->angular_momentum.z * 20.0f;
		//sphere_rb->AddTorque(temp_torque);
	}

	// Checks if a sphere has clipped into a plane, and returns how much the sphere needs to move to not clip: 
	glm::vec3 SphereToPlaneClipCheck(const glm::vec3 sphere_center0, const float radius, 
		const glm::vec3 plane_center, const glm::vec3 plane_normal, const glm::vec3 collision_point
	) {

		glm::vec3 delta_pos = glm::vec3(0.0f, 0.0f, 0.0f);

		// Calculate how far the sphere (minus the radius) is from the plane:
		float distance = DistanceToPlane(plane_normal, sphere_center0 - radius, plane_center);

		// Check for clipping on x-axis:
		if (plane_normal.x > 0.0f) {
			if (sphere_center0.x - radius <= plane_center.x) {
				delta_pos.x -= distance;
			}
		}
		else if (plane_normal.x < 0.0f) {
			if (sphere_center0.x + radius <= plane_center.x) {
				delta_pos.x += distance;
			}
		}

		// Check for clipping on y-axis:
		if (plane_normal.y > 0.0f) {
			if (sphere_center0.y - radius <= plane_center.y) {
				delta_pos.y -= distance;
			}
		}
		else if (plane_normal.y < 0.0f) {
			if (sphere_center0.y + radius <= plane_center.y) {
				delta_pos.y += distance;
			}
		}

		// Check for clipping on z-axis:
		if (plane_normal.z > 0.0f) {
			if (sphere_center0.z - radius <= plane_center.z) {
				delta_pos.z -= distance;
			}
		}
		else if (plane_normal.z < 0.0f) {
			if (sphere_center0.z + radius <= plane_center.z) {
				delta_pos.z += distance;
			}
		}

		return delta_pos;
	}

}
