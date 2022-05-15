#pragma once
#include <vector>
#include <memory>
#include <ext.hpp>

struct GameObject;
struct PhContext;
struct CollisionPoints;
struct SphereCollider;
struct Rigidbody;

struct PhysicsWorld {
	PhysicsWorld();
	void AddGameObject(std::shared_ptr<GameObject> gameobject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameobject);
	void Step(float delta_time);
	void TestCollisions(float delta_time, std::shared_ptr<GameObject> current_gameobj);
	void StartSimulation(std::shared_ptr<Rigidbody> rigidbody, std::shared_ptr<SphereCollider> collider);
	void CalcRotation(float delta_time, std::shared_ptr<Rigidbody> rigidbody);
	bool start;

private:
	friend struct PhContext;
	bool start_simulation;
	std::shared_ptr<PhContext> context;
	std::vector<std::shared_ptr<GameObject>> gameobjects;
};