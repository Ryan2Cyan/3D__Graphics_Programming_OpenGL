#pragma once
#include <memory>

struct PhysicsWorld;

struct PhContext
{
	std::shared_ptr<PhysicsWorld> CreatePhysicsWorld();

	std::weak_ptr<PhContext> self;
};