#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <string>
#include <ext.hpp>

struct GpContext;
struct Sampler;

struct Shader {

	Shader(std::string vert_path, std::string frag_path);
	void SetUniform(const std::string& u_name, glm::mat4 value);
	void SetSampler(const std::string& t_name, const std::shared_ptr<Sampler> sampler_arg);
	GLuint GetId();

private:
	friend struct GpContext;

	std::shared_ptr<GpContext> context;
	std::vector<std::shared_ptr<Sampler>> samplers;
	GLuint id;
	bool dirty;
	std::string vert_src;
	std::string frag_src;
};
