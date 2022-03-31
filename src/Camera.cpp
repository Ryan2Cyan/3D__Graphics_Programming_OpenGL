#include "Camera.h"
#include <iostream>

Camera::Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov_arg) {

	// Create projection mat:
	dimensions = win_size;
	if (ortho) {
		fov = 0.0f;
		proj = glm::ortho(0.0f, dimensions.x / 100.0f, 0.0f, dimensions.y / 100.0f, 0.0f, 100.0f);
	}
	else {
		fov = fov_arg;
		proj = glm::perspective(glm::radians(fov), dimensions.x / dimensions.y, 0.1f, 100.0f);
	}

	// Calculate camera view matrix:
	pos = position;
	tar = target;
	dir = glm::normalize(pos - tar);
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), dir));
	up = glm::cross(dir, right);
	view = glm::lookAt(pos, tar, up);


	// Set physics values:
	vel = { 0.0f, 0.0f, 0.0f };
	float yaw = -90.0f;
	float pitch = 0.0f;

	// Set other values:
	back_col = { 0.2f, 0.3f, 0.3f, 1.0f };
}

void Camera::MoveCam(SDL_Event &event, float deltaT, float cam_speed) {

	
}

void Camera::Refresh() {

	// Update view:
	view = glm::lookAt(pos, pos + dir, up);
}

void Camera::SetView(glm::mat4 arg) {
	view = arg;
}

glm::mat4 Camera::GetView() {
	return view;
}
