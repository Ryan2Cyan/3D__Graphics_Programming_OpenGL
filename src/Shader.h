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
	void SetUniform(const std::string& u_name, glm::vec4 value);
	void SetUniform(const std::string& u_name, GLuint value);
	/*void AddSampler(const std::shared_ptr<Sampler> arg);*/
	GLuint GetId();

	void Render(std::shared_ptr<Camera> cam, bool backface_cull);
	void Render(std::shared_ptr<Camera> cam, std::shared_ptr<RenderTexture> target, 
		std::shared_ptr<Shader> framebuffer_shader, std::shared_ptr<VertexArray> quad, 
		bool backface_cull);
	void Swap(std::shared_ptr<RenderTexture> source, std::shared_ptr<RenderTexture> destination, std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> quad, GLuint tex2 = 0);

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	std::vector<std::shared_ptr<Mesh>> meshes;
	GLuint id;
	bool dirty;
	std::string vert_src;
	std::string frag_src;
	bool polygon_mode;
};
