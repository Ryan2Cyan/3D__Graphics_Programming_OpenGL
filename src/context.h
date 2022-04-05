#pragma once
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>
#include <string>
#include <glfw/glfw3.h>
#include <vector>


struct Buffer;
struct VertexArray;
struct Shader;
struct Texture;
struct Sampler;
struct Mesh;
struct Camera;
struct RenderTexture;
struct CubeMap;

struct  GpContext
{
	// Utility functions:
	std::shared_ptr<VertexArray> Create2D(std::vector<glm::vec3> pos_coords);
	std::shared_ptr<VertexArray> Create2D(std::vector<glm::vec3> pos_coords, 
		std::vector<glm::vec2> tex_coords);
	std::shared_ptr<VertexArray> CreateUnitCube();

	// Input functions:
	void ProcessInput(GLFWwindow* window);
	void SetMainCamera(std::shared_ptr<Camera> arg);

	// Create object functions:
	std::shared_ptr<Buffer> CreateBuffer(); 
	std::shared_ptr<VertexArray> CreateVertexArray();
	std::shared_ptr<Shader> CreateShader(std::string vert_path, std::string frag_path);
	std::shared_ptr<Texture> CreateTexture(std::string tex_path);
	std::shared_ptr<CubeMap> CreateCubemap(std::vector<std::string> tex_faces);
	std::shared_ptr<Mesh> CreateMesh(std::string wf_filepath, glm::vec3 pos);
	std::shared_ptr<Mesh> CreateMesh(std::shared_ptr<VertexArray> vao, 
		std::shared_ptr<Texture> tex, glm::vec3 pos);
	std::shared_ptr<Camera> CreateCamera(bool ortho, glm::vec2 win_size, glm::vec3 position, glm::vec3 target,
		float fov);
	std::shared_ptr<RenderTexture> CreateRenderTexture(glm::ivec2 size);


	std::weak_ptr<GpContext> self;
private:
	std::shared_ptr<Camera> main_cam;
};