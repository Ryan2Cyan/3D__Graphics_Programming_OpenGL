#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <string>
#include <ext.hpp>

struct GpContext;
struct Sampler;
struct VertexArray;
struct Texture;
struct Mesh;
struct Camera;

struct Shader {

	Shader(std::string vert_path, std::string frag_path);
	~Shader();
	void AddMeshToRender(std::shared_ptr<Mesh> arg);
	void SetUniform(const std::string& u_name, glm::mat4 value);
	void SetUniform(const std::string& u_name, glm::vec3 value);
	/*void AddSampler(const std::shared_ptr<Sampler> arg);*/
	GLuint GetId();
	void Render(glm::ivec2 window_size, glm::vec4 background_col, bool backface_cull);
	void Render(std::shared_ptr<RenderTexture> target, std::shared_ptr<Shader> framebuffer_shader,
		std::shared_ptr<VertexArray> quad, glm::ivec2 window_size, glm::vec4 background_col, bool backface_cull);
	

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	std::vector<std::shared_ptr<Mesh>> meshes;
	GLuint id;
	bool dirty;
	std::string vert_src;
	std::string frag_src;
};
