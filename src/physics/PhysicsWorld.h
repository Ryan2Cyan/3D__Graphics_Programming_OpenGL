#pragma once
#include <vector>
#include <memory>
#include <ext.hpp>

struct GameObject;

struct PhysicsWorld {
	PhysicsWorld();
	void AddGameObject(std::shared_ptr<GameObject> gameobject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameobject);
	void Step(float delta_time);

private:
	std::vector<std::shared_ptr<GameObject>> gameobjects;
	glm::vec3 gravity;
};