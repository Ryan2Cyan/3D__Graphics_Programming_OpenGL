#pragma once
#include <memory>
#include <ext.hpp>
#include <SDL.h>

struct GpContext;
struct Shader;


struct Camera {

	Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
		float fov_arg);
	void MoveCam(SDL_Event& event, float deltaT, float cam_speed);
	void Refresh();


	glm::vec3 vel;
	glm::vec3 pos;
	glm::vec3 up;
	glm::vec3 front;
	glm::mat4 view;
	float yaw;
	float pitch;

private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;

	// Projection:
	glm::mat4 proj;
	glm::vec2 dimensions;

	// View:
	glm::vec3 tar;
	float fov;

	// Physics:

	// Other:
	glm::vec4 back_col;
};