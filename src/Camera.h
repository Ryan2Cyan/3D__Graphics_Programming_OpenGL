#pragma once
#include <memory>
#include <ext.hpp>
#include <vector>
#include <string>


struct GpContext;
struct Shader;
struct CubeMap;
struct VertexArray;

struct Camera {

	Camera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
		float fov);
	void Refresh();
	void SetView(glm::mat4 arg);
	void SetCubeMap(std::shared_ptr<CubeMap> arg);
	void SetCubeMapObj(std::shared_ptr<VertexArray> arg);
	const glm::mat4 GetView();
	const glm::mat4 GetProj();

	std::shared_ptr<CubeMap> cubemap;
	std::shared_ptr<VertexArray> cubemap_obj;
	std::shared_ptr<Shader> cubemap_shader;

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