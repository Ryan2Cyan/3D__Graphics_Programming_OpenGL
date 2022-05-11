#include "Camera.h"


Camera::Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
	float fov) {

	this->ortho = ortho;

	// Create projection mat:
	size = win_size;
	if (ortho) {
		fov = 0.0f;
		proj = glm::ortho(0.0f, size.x / 100.0f, 0.0f, size.y / 100.0f, 0.0f, 1000.0f);
	}
	else {
		this->fov = fov;
		proj = glm::perspective(glm::radians(this->fov), size.x / size.y, 0.1f, 1000.0f);
	}
	cubemap = nullptr;
	cubemap_shader = nullptr;
	transform.position = position;
	dir = glm::normalize(transform.position - target);
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), dir));
	up = glm::cross(dir, right);
	yaw = -90.0f;
	pitch = 0.0f;
	vel = { 0.0f, 0.0f, 0.0f };
	back_col = { 0.3f, 0.3f, 0.3f, 1.0f };
}

void Camera::Refresh() {

	// Adjust projection mat:
	if (ortho) {
		fov = 0.0f;
		proj = glm::ortho(0.0f, size.x / 100.0f, 0.0f, size.y / 100.0f, 0.0f, 1000.0f);
	}
	else {
		proj = glm::perspective(glm::radians(fov), size.x / size.y, 0.1f, 1000.0f);
	}

	// Calc dir:
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir = glm::normalize(dir);

	// Update view:
	view = glm::lookAt(transform.position, transform.position + dir, up);
}

void Camera::SetView(glm::mat4 arg) {
	view = arg;
}

void Camera::SetSize(glm::vec2 arg) {
	size = arg;
	Refresh();
}

void Camera::SetCubeMap(std::shared_ptr<CubeMap> arg) {
	cubemap = arg;
}

void Camera::SetCubeMapObj(std::shared_ptr<VertexArray> arg) {
	cubemap_obj = arg;
}

void Camera::SetCubeMapShader(std::shared_ptr<Shader> arg) {
	cubemap_shader = arg;
}

const glm::mat4 Camera::GetView() {
	return view;
}

const glm::mat4 Camera::GetProj() {
	return proj;
}

const glm::vec2 Camera::GetSize() {
	return size;
}

const Transform Camera::GetTransform() {
	return transform;
}