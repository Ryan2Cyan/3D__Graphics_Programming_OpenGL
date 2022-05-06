#pragma once
#include <vector>
#include <memory>
#include <ext.hpp>

struct GameObject;
struct PhContext;
struct CollisionPoints;

struct PhysicsWorld {
	PhysicsWorld();
	void AddGameObject(std::shared_ptr<GameObject> gameobject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameobject);
	void Step(float delta_time);
	bool start;

private:
	friend struct PhContext;

	std::shared_ptr<PhContext> context;
	std::vector<std::shared_ptr<GameObject>> gameobjects;
	glm::vec3 gravity;
	bool collision;
};