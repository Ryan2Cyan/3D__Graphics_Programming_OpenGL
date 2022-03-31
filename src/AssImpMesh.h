#pragma once
#include <string>
#include <GL/glew.h>
#include <ext.hpp>
#include <iostream>
#include <vector>

struct Shader;

struct AIvertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 tex_coord;
};

struct AItexture {
	GLuint id;
	std::string type;
};

struct AssImpMesh {
	
	AssImpMesh(std::vector<AIvertex> vert_arg, std::vector<GLuint> indi_arg,
		std::vector<AItexture> tex_arg);
	void Draw(std::shared_ptr<Shader> shader);

	std::vector<AIvertex> vertices;
	std::vector<GLuint> indices;
	std::vector<AItexture> textures;
	

private:
	GLuint vao_id;
	GLuint vbo_id;
	GLuint ebo_id;

	void SetUpMesh();
};