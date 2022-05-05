#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <string>
#include <ext.hpp>

struct GpContext;

struct Shader {

	Shader(std::string vert_path, std::string frag_path);
	~Shader();
	void AddGameObject(std::shared_ptr<GameObject> arg);
	/*void RemoveGameObject(std::shared_ptr<GameObject> arg);*/
	void SetUniform(const std::string& u_name, glm::mat4 value);
	void SetUniform(const std::string& u_name, glm::vec3 value);
	void SetUniform(const std::string& u_name, glm::vec4 value);
	void SetUniform(const std::string& u_name, GLuint value);
	/*void AddSampler(const std::shared_ptr<Sampler> arg);*/
	const GLuint GetId();

	void Render(std::shared_ptr<Camera> cam, bool backface_cull);
	void Render(std::shared_ptr<Camera> cam, std::shared_ptr<RenderTexture> target,
		bool backface_cull);
	void Swap(std::shared_ptr<RenderTexture> source, std::shared_ptr<RenderTexture> destination,
		GLuint tex_2);

	std::vector<std::shared_ptr<GameObject>> gameobjects;

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	GLuint id;
	bool dirty;
	std::string vert_src;
	std::string frag_src;
};
