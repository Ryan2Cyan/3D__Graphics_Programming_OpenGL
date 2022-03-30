#include "Camera.h"
#include <iostream>

Camera::Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov_arg) {

	// Create proj mat:
	dimensions = win_size;
	if (ortho) {
		fov = 0.0f;
		proj = glm::ortho(0.0f, dimensions.x / 100.0f, 0.0f, dimensions.y / 100.0f, 0.0f, 100.0f);
	}
	else {
		fov = fov_arg;
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

	// Set other values:
	back_col = { 0.2f, 0.3f, 0.3f, 1.0f };
}

void Camera::MoveCam(SDL_Event &event, float deltaT, float cam_speed) {

	// Increase velocity when user presses key:
	if (event.key.repeat == 0 && event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			vel += deltaT * cam_speed * front;
			break;
		case SDLK_s:
			vel -= deltaT * cam_speed * front;
			break;
		case SDLK_a:
			vel -= glm::normalize(glm::cross(front, up)) * cam_speed * deltaT;
			break;
		case SDLK_d:
			vel += glm::normalize(glm::cross(front, up)) * cam_speed * deltaT;
			break;
		case SDLK_q:
			vel += deltaT * cam_speed * up;
			break;
		case SDLK_e:
			vel -= deltaT * cam_speed * up;
			break;
		default:
			break;
		}
	}

	// Decrease velocity when user lets go of key:
	if (event.key.repeat == 0 && event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			vel -= deltaT * cam_speed * front;
			break;
		case SDLK_s:
			vel += deltaT * cam_speed * front;
			break;
		case SDLK_a:
			vel += glm::normalize(glm::cross(front, up)) * cam_speed * deltaT;
			break;
		case SDLK_d:
			vel -= glm::normalize(glm::cross(front, up)) * cam_speed * deltaT;
			break;
		case SDLK_q:
			vel -= deltaT * cam_speed * up;
			break;
		case SDLK_e:
			vel += deltaT * cam_speed * up;
			break;
		default:
			break;
		}
	}
}

void Camera::Refresh() {
	// Clamp velocity to prevent pos changing from small values:
	float threshold = 0.1;
	if (vel.x < threshold && vel.x > -threshold)
		vel.x = 0.0f;
	if (vel.y < threshold && vel.y > -threshold)
		vel.y = 0.00f;
	if (vel.z < threshold && vel.z > -threshold)
		vel.z = 0.0f;

	// Update position:
	pos += vel;

	// Update view:
	view = glm::lookAt(pos, pos + front, up);
}
