#include "Camera.h"
#include <iostream>

Camera::Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov_arg) {

	// Create projection mat:
	size = win_size;
	if (ortho) {
		fov = 0.0f;
		proj = glm::ortho(0.0f, size.x / 100.0f, 0.0f, size.y / 100.0f, 0.0f, 100.0f);
	}
	else {
		fov = fov_arg;
		proj = glm::perspective(glm::radians(fov), size.x / size.y, 0.1f, 100.0f);
	}

	pos = position;
	dir = glm::normalize(pos - target);
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), dir));
	up = glm::cross(dir, right);
	yaw = -90.0f;
	pitch = 0.0f;
	vel = { 0.0f, 0.0f, 0.0f };
	back_col = { 0.2f, 0.3f, 0.3f, 1.0f };
}

void Camera::Refresh() {

	// Calc dir:
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir = glm::normalize(dir);

	// Update view:
	view = glm::lookAt(pos, pos + dir, up);
}

void Camera::SetView(glm::mat4 arg) {
	view = arg;
}

const glm::mat4 Camera::GetView() {
	return view;
}
