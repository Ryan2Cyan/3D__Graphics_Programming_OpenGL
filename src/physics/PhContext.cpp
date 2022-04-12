#include "Ph.h"

std::shared_ptr<PhysicsWorld> PhContext::CreatePhysicsWorld() {

	std::shared_ptr<PhysicsWorld> physics_world = std::make_shared<PhysicsWorld>();
	physics_world->context = self.lock();
	return physics_world;
}