#include <ext.hpp>
#include <iostream>

int main() {
	
	// Calculate Jlinear force ////////////////////////////////////////////////////////////////////::
	float Jlinear = 0.0f;
	float e = 0.5f;
	float oneOverMass1 = 1.0f / 2.0f;
	float oneOverMass2 = 1.0f / 2.0f;
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
	float r1 = _bRadius;
	float mass = 2.0f;
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

	// Calculate Contact force ////////////////////////////////////////////////////////////////////:
	glm::vec3 contactForce;
	glm::vec3 gravityFroce = glm::vec3(0.0f, -9.8f * mass, 0.0f);
	glm::vec3 _force = glm::vec3(0.0f, -9.8f * mass, 0.0f);

	contactForce = -(_force)* contactNormal;;

	// Print output:
	std::cout << "Contact Force" << std::endl;
	std::cout << contactForce.x << ", " << contactForce.y << ", " << contactForce.z << std::endl;
	std::cout << std::endl;
}