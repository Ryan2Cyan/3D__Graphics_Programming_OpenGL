#include <ext.hpp>
#include <iostream>

int main() {
	
	// Calculate Jlinear force ////////////////////////////////////////////////////////////////////:
	bool _stopped = false;
	float delta_time = 0.05f;
	float Jlinear = 0.0f;
	float e = 0.5f;
	float mass = 2.0f;
	float oneOverMass1 = 1.0f / mass;
	float oneOverMass2 = 1.0f / mass;
	glm::vec3 vA = glm::vec3(0.0f, 20.0f, 0.0f);
	glm::vec3 contactNormal = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 pt1 = -(1.0f + e) * (vA);
	float pt2 = (glm::dot(pt1, contactNormal));
	Jlinear = (glm::dot(-(1.0f + e) * (vA), contactNormal)) / oneOverMass1 + oneOverMass2;


	// Print output:
	std::cout << "Linear Force" << std::endl;
	std::cout << vA.x << ", " << vA.y << ", " << vA.z << std::endl;
	std::cout << pt1.x << ", " << pt1.y << ", " << pt1.z << std::endl;
	std::cout << pt2 << std::endl;
	std::cout << Jlinear << std::endl;
	std::cout << std::endl;


	// Calculate Jangular force ////////////////////////////////////////////////////////////////////:
	float Jangular = 0.0f;
	float _bRadius = 2.0f;
	glm::vec3 r1 = _bRadius * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 vB = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 relativeVelocity = vA - vB;
	glm::mat3 _R = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
	glm::mat3 body_inertia = glm::mat3{
		(2.0f / 5.0f) * mass* std::pow(_bRadius, 2),0,0,
		0, (2.0f / 5.0f) * mass* std::pow(_bRadius, 2),0,
		0,0, (2.0f / 5.0f) * mass* std::pow(_bRadius, 2)
	};
	glm::mat3 _body_inertia_tensor_inverse = glm::inverse(body_inertia);
	glm::mat3 _inertia_tensor_inverse = _R * _body_inertia_tensor_inverse * glm::transpose(_R);

	float Jangular_pt1 = -(1.0f + e);
	float Jangular_pt2 = (glm::dot(Jangular_pt1 * (relativeVelocity), contactNormal));
	float Jangular_pt3 = glm::dot(_inertia_tensor_inverse * (r1 * contactNormal), contactNormal);
	Jangular = Jangular_pt2 / (oneOverMass1 + oneOverMass2) + Jangular_pt3;

	// Print output:
	std::cout << "Angular Force" << std::endl;
	std::cout << Jangular_pt1 << std::endl;
	std::cout << Jangular_pt2 << std::endl;
	std::cout << Jangular_pt3 << std::endl;
	std::cout << Jangular << std::endl;
	std::cout << std::endl;

	// Calculate Impulse force ////////////////////////////////////////////////////////////////////:
	glm::vec3 impulseForce;

	float impulse_pt1 = Jlinear + Jangular;
	glm::vec3 impulse_pt2 = impulse_pt1 * contactNormal;

	// Print output:
	std::cout << "Impulse Force" << std::endl;
	std::cout << impulse_pt1 << std::endl;
	std::cout << impulse_pt2.x << ", " << impulse_pt2.y << ", " << impulse_pt2.z << std::endl;
	std::cout << std::endl;

	// Calculate Contact force ////////////////////////////////////////////////////////////////////:
	glm::vec3 contactForce;
	glm::vec3 gravityFroce = glm::vec3(0.0f, -9.8f * mass, 0.0f);
	glm::vec3 _force = glm::vec3(0.0f, -9.8f * mass, 0.0f);
	
	contactForce = -(_force)* contactNormal;;

	// Print output:
	std::cout << "Contact Force" << std::endl;
	std::cout << contactForce.x << ", " << contactForce.y << ", " << contactForce.z << std::endl;
	std::cout << std::endl;

	// Calculate Forward Relative Velocity ////////////////////////////////////////////////////////////////////:
	glm::vec3 forwardRelativeVelocity;

	float frv_pt1 = glm::dot(relativeVelocity, contactNormal);
	glm::vec3 frv_pt2 = frv_pt1 * contactNormal;
	forwardRelativeVelocity = relativeVelocity - frv_pt1;

	// Print output:
	std::cout << "Forward Relative Velocity" << std::endl;
	std::cout << relativeVelocity.x << ", " << relativeVelocity.y << ", " << relativeVelocity.z << std::endl;
	std::cout << frv_pt1 << std::endl;
	std::cout << frv_pt2.x << ", " << frv_pt2.y << ", " << frv_pt2.z << std::endl;
	std::cout << forwardRelativeVelocity.x << ", " << forwardRelativeVelocity.y << ", " << forwardRelativeVelocity.z << std::endl;
	std::cout << std::endl;

	// Calculate Forward Relative Direction ////////////////////////////////////////////////////////////////////:
	glm::vec3 forwardRelativeDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	
	if (forwardRelativeVelocity != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		forwardRelativeDirection = glm::normalize(forwardRelativeVelocity); // gets a normalized vector of the direction travelled perpendicular to the contact normal
	}

	// Print output:
	std::cout << "Forward Relative Direction" << std::endl;
	std::cout << forwardRelativeDirection.x << ", " << forwardRelativeDirection.y << ", " << forwardRelativeDirection.z << std::endl;
	std::cout << std::endl;


	// Calculate Friction Direction ////////////////////////////////////////////////////////////////////:
	float mu = 0.5f;

	glm::vec3 frictionDirection = forwardRelativeDirection * -1.0f;

	// Print output:
	std::cout << "Friction Direction" << std::endl;
	std::cout << frictionDirection.x << ", " << frictionDirection.y << ", " << frictionDirection.z << std::endl;
	std::cout << std::endl;

	// Calculate Friction Force //////////////////////////////////////////////////////////////////////:
	float frictForce_pt1 = glm::length(contactForce);
	glm::vec3 frictionForce = frictionDirection * mu * frictForce_pt1; // friction = mu * normal force

	// Print output:
	std::cout << "Friction Force" << std::endl;
	std::cout << frictForce_pt1 << std::endl;
	std::cout << frictionForce.x << ", " << frictionForce.y << ", " << frictionForce.z << std::endl;
	std::cout << std::endl;

	// Applying Friction Force //////////////////////////////////////////////////////////////////////:

	// Print output:
	std::cout << "Applying Friction Force" << std::endl;
	std::cout << glm::length(forwardRelativeVelocity) << std::endl;
	std::cout << ((glm::length(frictionForce) / mass)* delta_time) << std::endl;
	std::cout << glm::length(forwardRelativeVelocity) - ((glm::length(frictionForce) / mass)* delta_time) << std::endl;
	
	if (glm::length(forwardRelativeVelocity) - ((glm::length(frictionForce) / mass) * delta_time) > 0.0f) // Checks to see if the friction force would reverse the direction of travel
	{
		// AddForce(frictionForce);	// Adds the friction
		std::cout << "Continue: Add Force: " << frictionForce.x << ", " << frictionForce.y << ", " << frictionForce.z << std::endl;
	}
	else
	{
		frictionForce = forwardRelativeVelocity * -1.0f; // Adds enough friction to stop the object
		std::cout << "Stop: Add Force: " << frictionForce.x << ", " << frictionForce.y << ", " << frictionForce.z << std::endl;
		// AddForce(frictionForce);
		_stopped = true;
	}

	std::cout << std::endl;

	// Calculating Torque //////////////////////////////////////////////////////////////////////:
	glm::vec3 torque_pt1 = glm::cross(r1, contactForce);
	glm::vec3 torque_pt2 = glm::cross(r1, frictionForce);
	glm::vec3 tempTorque = torque_pt1 + torque_pt2;

	// Print output:
	std::cout << "Calculating Torque" << std::endl;
	std::cout << torque_pt1.x << ", " << torque_pt1.y << ", " << torque_pt1.z << std::endl;
	std::cout << torque_pt2.x << ", " << torque_pt2.y << ", " << torque_pt2.z << std::endl;
	std::cout << tempTorque.x << ", " << tempTorque.y << ", " << tempTorque.z << std::endl;
	std::cout << std::endl;

	// Applying Torque //////////////////////////////////////////////////////////////////////:
	glm::vec3 angular_momentum = glm::vec3(0.0f, 0.0f, 0.0f);
	tempTorque.x -= angular_momentum.x * 20.0f;
	tempTorque.z -= angular_momentum.z * 20.0f; // A damper to slow the rotation over time:

	// Print output:
	std::cout << "Applying Torque" << std::endl;
	std::cout << tempTorque.x << ", " << tempTorque.y << ", " << tempTorque.z << std::endl;
	std::cout << std::endl;
}