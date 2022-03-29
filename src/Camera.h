#pragma once
#include <memory>
#include <ext.hpp>

struct GpContext;
struct Shader;


struct Camera {
	Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
		float fov_arg);


	glm::vec3 vel;
	glm::vec3 pos;
	glm::vec3 up;
	glm::vec3 front;
	glm::mat4 view;

private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;
	glm::mat4 proj;
	glm::vec2 dimensions;
	glm::vec3 tar;
	float fov;
	float yaw;
	float pitch;
};