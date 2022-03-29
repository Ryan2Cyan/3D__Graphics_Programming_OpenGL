#include "Camera.h"

Camera::Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov_arg) {

	// Create proj mat:
	dimensions = win_size;
	if (ortho) {
		proj = glm::ortho(0.0f, dimensions.x, 0.0f, dimensions.y, 0.0f, 1.0f);
	}
	else {
		proj = glm::perspective(glm::radians(fov), dimensions.x / dimensions.y, 0.1f, 100.0f);
	}

	// Set the view mat:
	pos = position;
	tar = target;
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	view = glm::lookAt(pos, tar, up);
	float yaw = -90.0f;
	float pitch = 0.0f;

	// Set physics values:
	vel = { 0.0f, 0.0f, 0.0f };
}

