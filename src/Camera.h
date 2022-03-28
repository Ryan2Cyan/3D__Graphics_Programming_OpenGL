#pragma once
#include <memory>
#include <ext.hpp>

struct GpContext;


struct Camera {
	Camera(glm::vec3 position, glm::vec3 target);

	glm::mat4 view;
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 tar;
	glm::vec3 up;
	glm::vec3 front;
	float yaw;
	float pitch;


private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
};