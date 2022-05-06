#include <algorithm>
#include <graphics/GameObject.h>
#include "PhysicsWorld.h"
#include "Utility.h"
#include "CollisionPoints.h"


PhysicsWorld::PhysicsWorld() {
	gravity = glm::vec3(0.0f, -9.81f, 0.0f);
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

	delta_time = 0.1f;
	if (start) {

		// Loop through all gameobjects and secure their rigidbodies and transform components:
		for (std::shared_ptr<GameObject> gameobject : gameobjects) {
			if (gameobject->GetRigidbody() != nullptr) {
				std::shared_ptr<Rigidbody> rigidbody = gameobject->GetRigidbody();
				std::shared_ptr<Transform> transform = gameobject->GetTransform();

				// Negatively translate to return to 0:
				gameobject->Translate(-transform->position);

				// Apply force:
				rigidbody->force += rigidbody->mass * gravity;

				// Update object's velocity, then position:
				rigidbody->velocity += rigidbody->force / rigidbody->mass * delta_time;
				transform->position += rigidbody->velocity * delta_time;
				if (transform->position.y <= 0.0f)
					transform->position.y = 0.0f;

				gameobject->Translate(transform->position);

				// Reset net force each frame:
				rigidbody->force = glm::vec3(0.0f, 0.0f, 0.0f);
			}
		}

		// Loop through all gameobjects with colliders and compare with each object with collider:
		for (size_t i = 0; i < gameobjects.size(); i++){

			// Check if the current object has a collider and rigidbody:
			std::shared_ptr<Collider> currentCol;
			if (gameobjects[i]->GetCollider()) 
				currentCol = gameobjects[i]->GetCollider();
			else
				continue;

			for (size_t j = 0; j < gameobjects.size(); j++) {
				std::shared_ptr<Collider> otherCol;

				// Check if other object has a collider:
				if (gameobjects[j]->GetCollider()) 
					otherCol = gameobjects[j]->GetCollider();
				else
					continue;

				// Check if other collider is different to current collider:
				if (currentCol == otherCol)
					continue;

				// Check for collision based on type:
				glm::vec3 collision_point;
				if (auto col_0 = std::dynamic_pointer_cast<SphereCollider>(currentCol)) {

					if (auto col_1 = std::dynamic_pointer_cast<SphereCollider>(otherCol)) {
					
						// Sphere to sphere collision:
						if (PFG::SphereToSphereCollision(col_0->center, col_1->center, col_0->radius, col_1->radius, collision_point)) {
						
							std::cout << "Sphere to sphere collision" << std::endl;
						}
					}
					else if (auto col_1 = std::dynamic_pointer_cast<PlaneCollider>(otherCol)) {
						// Sphere to plane collision:
						if (PFG::MovingSphereToPlaneCollision(col_1->normal, col_0->center, col_0->center + gameobjects[i]->GetRigidbody()->velocity * delta_time, 
							col_1->center, col_0->radius, collision_point)) {
						
							std::cout << "Sphere to plane collision" << std::endl;

						}
					}
				}

				else if (auto col_0 = std::dynamic_pointer_cast<PlaneCollider>(currentCol)) {

					if (auto col_1 = std::dynamic_pointer_cast<SphereCollider>(otherCol)) {
						// Plane to sphere collision:
						if (PFG::MovingSphereToPlaneCollision(col_0->normal, col_1->center, col_1->center + gameobjects[j]->GetRigidbody()->velocity * delta_time,
							col_0->center, col_1->radius, collision_point)){
							
							std::cout << "Plane to sphere collision" << std::endl;
						}
					
					}
					else if (auto col_1 = std::dynamic_pointer_cast<PlaneCollider>(otherCol)) {
						// Plane to plane collision:
						if (PFG::DistanceToPlane(col_0->center, col_1->center, collision_point)) {
			
							std::cout << "Plane to plane collision" << std::endl;
						}
					}
				}
			
			}
		}
	}
}