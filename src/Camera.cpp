#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target) {

	pos = position;
	tar = target;
	vel = { 0.0f, 0.0f, 0.0f };
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	view = glm::lookAt(pos, tar, up);
}

