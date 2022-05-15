#include <algorithm>
#include <graphics/GameObject.h>
#include "PhysicsWorld.h"
#include "Utility.h"
#include "CollisionPoints.h"
#include "Rigidbody.h"
#include "Collider.h"


PhysicsWorld::PhysicsWorld() {
	start = false;
	start_simulation = false;
}

void PhysicsWorld::AddGameObject(std::shared_ptr<GameObject> gameobject) {
	gameobjects.push_back(gameobject);
}

void PhysicsWorld::RemoveGameObject(std::shared_ptr<GameObject> gameobject) {
	gameobjects.erase(std::remove(gameobjects.begin(), gameobjects.end(), gameobject), gameobjects.end());
}


// Calculates dynamic physics for all gameobjects in PhysicsWorld::gameobjects (F = ma):
void PhysicsWorld::Step(float delta_time) {

	delta_time = 0.05f;
	if (start) {

		// Set values for each gameObject:
		for (size_t i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->rigidBody && gameobjects[i]->collider) {
				if (auto col_0 = std::dynamic_pointer_cast<SphereCollider>(gameobjects[i]->collider)) {

					StartSimulation(gameobjects[i]->rigidBody, col_0);
				}
			}
		}

		start = false;
		start_simulation = true;
	}

	if (start_simulation) {

		// Loop through all gameobjects and secure their rigidbodies and transform components:
		for (size_t i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->GetRigidbody() != nullptr) {
				std::shared_ptr<Rigidbody> rigidbody = gameobjects[i]->GetRigidbody();
				std::shared_ptr<Transform> transform = gameobjects[i]->GetTransform();

				// Reset net force each frame:
				rigidbody->force = glm::vec3(0.0f, 0.0f, 0.0f);
				rigidbody->torque = glm::vec3(0.0f, 0.0f, 0.0f);

				TestCollisions(delta_time, gameobjects[i]);

				// Apply gravity:
				if (rigidbody->apply_gravity)
					rigidbody->force += rigidbody->mass * rigidbody->gravity;

				// Update object's velocity, then position:
				rigidbody->velocity += rigidbody->force / rigidbody->mass * delta_time;
				glm::vec3 delta_pos = rigidbody->velocity * delta_time;

				if (gameobjects[i]->name == "new-sphere") {
					std::cout << "Applied Force: " << rigidbody->force.x << ",  " << rigidbody->force.y << ",  " << rigidbody->force.z << std::endl;
					std::cout << "Position: " << transform->position.x << ",  " << transform->position.y << ",  " << transform->position.z << std::endl;
					std::cout << "Velocity: " << rigidbody->velocity.x << ",  " << rigidbody->velocity.y << ",  " << rigidbody->velocity.z << std::endl;
				}
				
				// Check if the object's velocity is very small, if it is, stop it from moving:
				if (rigidbody->velocity.x <= 0.5f && rigidbody->velocity.x >= -0.5f) 
					delta_pos.x = 0.0f;
				if (rigidbody->velocity.y <= 0.5f && rigidbody->velocity.y >= -0.5f) 
					delta_pos.y = 0.0f;
				if (rigidbody->velocity.z <= 0.5f && rigidbody->velocity.z >= -0.5f) 
					delta_pos.z = 0.0f;

				CalcRotation(delta_time, rigidbody);
				
				//// Move the object:
				if (gameobjects[i]->name == "new-sphere") {
					/*glm::mat4 model_rot = glm::mat4(rigidbody->rotation);
					glm::quat rot = glm::normalize(glm::quat_cast(rigidbody->rotation));
					rigidbody->rotation = glm::mat3_cast(rot);
					gameobjects[i]->SetModelMat(gameobjects[i]->GetModelMat() * glm::mat4_cast(rot));*/

					gameobjects[i]->Translate(delta_pos);
				}
			}
		}

	}
}

// Checks collisions against all physics objects in the scene. Applies appropriate force upon collision:
void PhysicsWorld::TestCollisions(float delta_time, std::shared_ptr<GameObject> current_gameobj) {

	// Check if the current object has a collider and rigidbody:
	std::shared_ptr<Collider> current_col;
	if (current_gameobj->GetCollider() && current_gameobj->GetRigidbody()) {
		current_col = current_gameobj->GetCollider();
		current_col->center = current_gameobj->GetTransform()->position;
		current_gameobj->rigidBody->has_collided = false;
	}
	else
		exit;

	// Loop through every other physics gameobject to check for collisions:
	for (size_t j = 0; j < gameobjects.size(); j++) {
		std::shared_ptr<GameObject> other_gameobj = gameobjects[j];

		// Check if other object has a collider:
		std::shared_ptr<Collider> other_col;
		if (other_gameobj->GetCollider() && other_gameobj->GetRigidbody()) {
			other_col = other_gameobj->GetCollider();
			other_col->center = other_gameobj->GetTransform()->position;
		}
		else
			continue;

		// Check if other collider is different to current collider:
		if (current_col == other_col)
			continue;

		// Check for collision based on type:
		glm::vec3 collision_point;
		if (auto col_0 = std::dynamic_pointer_cast<SphereCollider>(current_col)) {

			// SPHERE-TO-SPHERE COLLISION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (auto col_1 = std::dynamic_pointer_cast<SphereCollider>(other_col)) {
				current_gameobj->rigidBody->has_collided = true;
				if (Pfg::SphereToSphereCollision(col_0->center, col_1->center, col_0->radius, col_1->radius, collision_point)) {
					
					//// Apply contact force:
					//current_gameobj->rigidBody->AddForce(-current_gameobj->rigidBody->gravity * current_gameobj->rigidBody->mass);

					//// Calculate the normal between the two collision points:
					//glm::vec3 normal = glm::normalize(col_1->center - col_0->center);

					//// Add impulse force:
					//glm::vec3 impulse_force = Pfg::ImpulseSolver(delta_time, col_0->elasticity, current_gameobj->rigidBody->mass,
					//	other_gameobj->rigidBody->mass, current_gameobj->rigidBody->velocity, other_gameobj->rigidBody->velocity,
					//	normal);

					//// Apply impulse force:
					//current_gameobj->rigidBody->AddForce(impulse_force);
				}

			}
			// SPHERE-TO-PLANE COLLISION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (auto col_1 = std::dynamic_pointer_cast<PlaneCollider>(other_col)) {
				if (Pfg::MovingSphereToPlaneCollision(col_1->normal, col_0->center, col_0->center + current_gameobj->GetRigidbody()->velocity * delta_time,
					col_1->center, col_0->radius, collision_point)) {

					current_gameobj->rigidBody->has_collided = true;

					// Check if sphere is clipping with the plane:
					current_gameobj->Translate(Pfg::SphereToPlaneClipCheck(col_0->center, col_0->radius, col_1->center, col_1->normal, collision_point));

					// Calculate the normal between the two collision points:
					glm::vec3 normal = glm::normalize(col_1->center - col_0->center);

					// Calculate impulse force:
					Pfg::ImpulseSolver( delta_time, col_0, current_gameobj->rigidBody, other_gameobj->rigidBody,
						normal);
				}
			}
		}
	}
}

void PhysicsWorld::StartSimulation(std::shared_ptr<Rigidbody> rigidbody, std::shared_ptr<SphereCollider> collider) {

	rigidbody->rotation_quaterion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	// Compute body inertia:
	glm::mat3 body_inertia;
	body_inertia = glm::mat3{
		(2.0f / 5.0f) * rigidbody->mass * std::pow(collider->radius, 2), 0.0f, 0.0f,
		0.0f, (2.0f / 5.0f) * rigidbody->mass * std::pow(collider->radius, 2.0f), 0.0f,
		0.0f, 0.0f, (2.0f / 5.0f) * rigidbody->mass * std::pow(collider->radius, 2.0f)
	};

	// Inverse body inertia:
	rigidbody->body_inertia_tensor_inverse = glm::inverse(body_inertia);
	rigidbody->interia_tensor_inverse = rigidbody->rotation *
		rigidbody->body_inertia_tensor_inverse * glm::transpose(rigidbody->rotation);
	rigidbody->angular_velocity = rigidbody->interia_tensor_inverse * rigidbody->angular_momentum;

}

void PhysicsWorld::CalcRotation(float delta_time, std::shared_ptr<Rigidbody> rigidbody) {

	// Compute current angular momentum:
	rigidbody->angular_momentum = rigidbody->torque * delta_time;

	// Calculate inverse inertia tensor:
	rigidbody->interia_tensor_inverse = rigidbody->rotation *
		rigidbody->body_inertia_tensor_inverse * glm::transpose(rigidbody->rotation);

	// Update angular velocity:
	rigidbody->angular_velocity = rigidbody->interia_tensor_inverse * rigidbody->angular_momentum;

	// Calculate skew matrix omega star:
	glm::mat3 omega_star = glm::mat3(0.0f, -rigidbody->angular_velocity.z, rigidbody->angular_velocity.y,
		rigidbody->angular_velocity.z, 0.0f, -rigidbody->angular_velocity.x,
		-rigidbody->angular_velocity.y, rigidbody->angular_velocity.x, 0.0f);

	glm::quat angle_velocity_quaternion = glm::quat(0.0f, -rigidbody->angular_velocity.x,
		-rigidbody->angular_velocity.y, -rigidbody->angular_velocity.z);

	rigidbody->rotation_quaterion += 0.5f * rigidbody->rotation_quaterion * angle_velocity_quaternion * delta_time;
	rigidbody->rotation_quaterion = glm::normalize(rigidbody->rotation_quaterion);
}