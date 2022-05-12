#include <algorithm>
#include <graphics/GameObject.h>
#include "PhysicsWorld.h"
#include "Utility.h"
#include "CollisionPoints.h"


PhysicsWorld::PhysicsWorld() {
	start = false;
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

		// Loop through all gameobjects and secure their rigidbodies and transform components:
		for (size_t i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->GetRigidbody() != nullptr) {
				std::shared_ptr<Rigidbody> rigidbody = gameobjects[i]->GetRigidbody();
				std::shared_ptr<Transform> transform = gameobjects[i]->GetTransform();

				// Reset net force each frame:
				rigidbody->force = glm::vec3(0.0f, 0.0f, 0.0f);

				// Apply gravity:
				if (rigidbody->apply_gravity)
					rigidbody->force += rigidbody->mass * rigidbody->gravity;

				TestCollisions(delta_time, gameobjects[i]);

				// Update object's velocity, then position:
				rigidbody->velocity += rigidbody->force / rigidbody->mass * delta_time;
				glm::vec3 delta_pos = rigidbody->velocity * delta_time;
				gameobjects[i]->Translate(delta_pos);

				if (gameobjects[i]->name == "new-sphere")
					std::cout << "Applied Force: " << rigidbody->force.x << ",  " << rigidbody->force.y << ",  " << rigidbody->force.z << std::endl;
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
					
					// Apply contact force:
					current_gameobj->rigidBody->AddForce(-current_gameobj->rigidBody->gravity * current_gameobj->rigidBody->mass);

					// Calculate the normal between the two collision points:
					glm::vec3 normal = glm::normalize(col_1->center - col_0->center);

					// Add impulse force:
					glm::vec3 impulse_force = Pfg::ImpulseSolver(delta_time, col_0->elasticity, current_gameobj->rigidBody->mass,
						other_gameobj->rigidBody->mass, current_gameobj->rigidBody->velocity, other_gameobj->rigidBody->velocity,
						normal);

					// Apply impulse force:
					current_gameobj->rigidBody->AddForce(impulse_force);
				}

			}
			// SPHERE-TO-PLANE COLLISION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (auto col_1 = std::dynamic_pointer_cast<PlaneCollider>(other_col)) {
				if (Pfg::MovingSphereToPlaneCollision(col_1->normal, col_0->center, col_0->center + current_gameobj->GetRigidbody()->velocity * delta_time,
					col_1->center, col_0->radius, collision_point)) {
					current_gameobj->rigidBody->has_collided = true;

					// Check if sphere is clipping with the plane:
					current_gameobj->Translate(Pfg::SphereToPlaneClipCheck(col_0->center, col_0->radius, col_1->center, col_1->normal, collision_point));
				

					// Apply contact force:
					current_gameobj->rigidBody->AddForce(-current_gameobj->rigidBody->gravity * current_gameobj->rigidBody->mass);

					// Calculate the normal between the two collision points:
					glm::vec3 normal = glm::normalize(col_1->center - col_0->center);

					// Calculate impulse force:
					glm::vec3 impulse_force = Pfg::ImpulseSolver( delta_time, current_gameobj->collider->elasticity, 
						current_gameobj->rigidBody->mass, other_gameobj->rigidBody->mass, current_gameobj->rigidBody->velocity,
						other_gameobj->rigidBody->velocity,normal);

					// Apply impulse force:
					current_gameobj->rigidBody->AddForce(impulse_force);
				}
			}
		}
	}
}

