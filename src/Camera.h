#pragma once
#include <memory>
#include <ext.hpp>
#include <SDL.h>

struct GpContext;
struct Shader;


struct Camera {

	Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
		float fov_arg);
	void Refresh();
	void SetView(glm::mat4 arg);
	const glm::mat4 GetView();

	
private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;

	// Values:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 view;
	float yaw;
	float pitch;

	// Projection:
	glm::mat4 proj;
	glm::vec2 size;

	// View:
	float fov;

	// Physics:
	glm::vec3 vel;

	// Other:
	glm::vec4 back_col;
};