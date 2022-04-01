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
	glm::vec3 MouseCallback(float x, float y);
	void Refresh();

	void SetView(glm::mat4 arg);
	glm::mat4 GetView();

	glm::vec3 pos;
	glm::vec3 dir;
private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;

	// Values:

	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 view;
	float yaw;
	float pitch;

	// Projection:
	glm::mat4 proj;
	glm::vec2 dimensions;

	// View:
	glm::vec3 tar;
	float fov;

	// Physics:
	glm::vec3 vel;

	// Other:
	float movement_speed;
	glm::vec4 back_col;
};