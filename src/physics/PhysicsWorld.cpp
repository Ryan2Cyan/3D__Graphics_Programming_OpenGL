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

				// Check if the current object has a collider and rigidbody:
				std::shared_ptr<Collider> currentCol;
				if (gameobjects[i]->GetCollider() && gameobjects[i]->GetRigidbody()) {
					currentCol = gameobjects[i]->GetCollider();
					currentCol->center = gameobjects[i]->GetTransform()->position;
					gameobjects[i]->rigidBody->has_collided = false;
				}
				else
					continue;

				for (size_t j = 0; j < gameobjects.size(); j++) {
					std::shared_ptr<Collider> otherCol;

					// Check if other object has a collider:
					if (gameobjects[j]->GetCollider() && gameobjects[j]->GetRigidbody()) {
						otherCol = gameobjects[j]->GetCollider();
						otherCol->center = gameobjects[j]->GetTransform()->position;
					}
					else
						continue;

					// Check if other collider is different to current collider:
					if (currentCol == otherCol)
						continue;

					// Check for collision based on type:
					glm::vec3 collision_point;
					if (auto col_0 = std::dynamic_pointer_cast<SphereCollider>(currentCol)) {

						if (auto col_1 = std::dynamic_pointer_cast<SphereCollider>(otherCol)) {
							// Sphere-sphere collision

						}
						else if (auto col_1 = std::dynamic_pointer_cast<PlaneCollider>(otherCol)) {
							// Sphere to plane collision:
							if (Pfg::MovingSphereToPlaneCollision(col_1->normal, col_0->center, col_0->center + gameobjects[i]->GetRigidbody()->velocity * delta_time,
								col_1->center, col_0->radius, collision_point)) {

								gameobjects[i]->rigidBody->AddForce(-gameobjects[i]->rigidBody->gravity * gameobjects[i]->rigidBody->mass);

								// Apply impulse force:
								glm::vec3 impulse_force = Pfg::ImpulseSolver(
									delta_time, gameobjects[i]->collider->elasticity, gameobjects[i]->rigidBody->mass,
									gameobjects[j]->rigidBody->mass, gameobjects[i]->rigidBody->velocity, gameobjects[j]->rigidBody->velocity,
									glm::normalize(col_1->center - col_0->center));

								gameobjects[i]->rigidBody->AddForce(impulse_force);
							}
						}
					}
				}

				// Update object's velocity, then position:
				rigidbody->velocity += rigidbody->force / rigidbody->mass * delta_time;
				glm::vec3 delta_pos = rigidbody->velocity * delta_time;
				gameobjects[i]->Translate(delta_pos);

				if (gameobjects[i]->name == "new-sphere")
					std::cout << "Applied Force: " << rigidbody->force.x << ",  " << rigidbody->force.y << ",  " << rigidbody->force.z << std::endl;
			}
		}

		//// Loop through all gameobjects with colliders and compare with each object with collider:
		//for (size_t i = 0; i < gameobjects.size(); i++){

		//	// Check if the current object has a collider and rigidbody:
		//	std::shared_ptr<Collider> currentCol;
		//	if (gameobjects[i]->GetCollider() && gameobjects[i]->GetRigidbody()) {
		//		currentCol = gameobjects[i]->GetCollider();
		//		currentCol->center = gameobjects[i]->GetTransform()->position;
		//		gameobjects[i]->rigidBody->has_collided = false;
		//	}
		//	else
		//		continue;

		//	for (size_t j = 0; j < gameobjects.size(); j++) {
		//		std::shared_ptr<Collider> otherCol;

		//		// Check if other object has a collider:
		//		if (gameobjects[j]->GetCollider() && gameobjects[j]->GetRigidbody()) {
		//			otherCol = gameobjects[j]->GetCollider();
		//			otherCol->center = gameobjects[j]->GetTransform()->position;
		//		}
		//		else
		//			continue;

		//		// Check if other collider is different to current collider:
		//		if (currentCol == otherCol)
		//			continue;

		//		// Check for collision based on type:
		//		glm::vec3 collision_point;
		//		if (auto col_0 = std::dynamic_pointer_cast<SphereCollider>(currentCol)) {

		//			if (auto col_1 = std::dynamic_pointer_cast<SphereCollider>(otherCol)) {
		//			
		//			
		//			}
		//			else if (auto col_1 = std::dynamic_pointer_cast<PlaneCollider>(otherCol)) {
		//				// Sphere to plane collision:
		//				if (Pfg::MovingSphereToPlaneCollision(col_1->normal, col_0->center, col_0->center + gameobjects[i]->GetRigidbody()->velocity * delta_time, 
		//					col_1->center, col_0->radius, collision_point)) {

		//					// Apply impulse force:
		//					gameobjects[i]->rigidBody->AddForce(Pfg::ImpulseSolver(
		//						delta_time, gameobjects[i]->collider->elasticity, gameobjects[i]->rigidBody->mass,
		//						gameobjects[j]->rigidBody->mass, gameobjects[i]->rigidBody->velocity, gameobjects[j]->rigidBody->velocity,
		//						glm::normalize(col_1->center - col_0->center)
		//					));

		//					// Reset the velocity:
		//					/*gameobjects[i]->rigidBody->velocity = glm::vec3(0.0f, 0.0f, 0.0f);*/

		//					// Check object is outside of the collider plane:
		//					if (Pfg::DistanceToPlane(col_1->normal, col_0->center, col_1->center) <= col_0->radius) {

		//						//gameobjects[i]->Translate(gameobjects[i]->transform->position + (col_1->normal * col_0->radius));
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

	}
}