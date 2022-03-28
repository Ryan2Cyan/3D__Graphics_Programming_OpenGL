#pragma once
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>
#include <string>


struct Buffer;
struct VertexArray;
struct Shader;
struct Texture;
struct Sampler;
struct Mesh;
struct Camera;
struct RenderTexture;

struct  GpContext
{
	// Utility functions:
	std::shared_ptr<VertexArray> CreateTriangle();
	std::shared_ptr<VertexArray> Create2DImage();

	// Create object functions:
	std::shared_ptr<Buffer> CreateBuffer(); 
	std::shared_ptr<VertexArray> CreateVertexArray();
	std::shared_ptr<Shader> CreateShader(std::string vert_path, std::string frag_path);
	std::shared_ptr<Texture> CreateTexture(std::string tex_path);
	/*std::shared_ptr<Sampler> CreateSampler();*/
	std::shared_ptr<Mesh> CreateMesh(std::string filepath, glm::vec3 pos_arg);
	std::shared_ptr<Camera> CreateCamera(glm::vec3 position, glm::vec3 target);
	std::shared_ptr<RenderTexture> CreateRenderTexture(glm::ivec2 size);

	std::weak_ptr<GpContext> self;

private:
};