#include "Texture.h"
//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

// Texture~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Texture::Texture(std::string tex_path) {

	// Save the filepath:
	filepath = tex_path;

	// Init other members:
	id = 0;
	dirty = true;
}

Texture::~Texture() {
	GLuint del_id = id;
	glDeleteTextures(1, &del_id);
}

// Sends the loaded texture to the GPU and returns the texture ID:
const GLuint Texture::GetId() {

	if (dirty) {

		// Load image/texture from filepath:
		int w = 0;
		int h = 0;
		const char* s = filepath.c_str();
		unsigned char* data = stbi_load(s, &w, &h, NULL, 4);
		
		if (!id) {
			// Generate the texture:
			glGenTextures(1, &id);
		}
		if (!id)
			throw std::exception("Unable to generate texture");

		// Send texture data to GPU:
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
		free(data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		dirty = false;
	}
	return id;
}


// CubeMap~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CubeMap::CubeMap(std::vector<std::string> tex_faces){

	// Save the filepath:
	this->tex_faces = tex_faces;

	// Init other members:
	id = 0;
	dirty = true;
}

CubeMap::~CubeMap() {
	GLuint del_id = id;
	glDeleteTextures(1, &del_id);
}

// Sends the loaded texture to the GPU and returns the texture ID:
const GLuint CubeMap::GetId() {

	if (dirty) {

		// Generate texture for cube map:
		if (!id) glGenTextures(1, &id);
		if (!id) throw std::exception("Unable to generate texture");

		glBindTexture(GL_TEXTURE_CUBE_MAP, id);

		// Load 6 images/textures from filepaths:
		int w = 0;
		int h = 0;
		int channels = 0;
		for (size_t i = 0; i < tex_faces.size(); i++)
		{
			const char* s = tex_faces[i].c_str();
			unsigned char* data = stbi_load(s, &w, &h, &channels, 0);
			// If image loads correctly, send data into GPU:
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else {
				std::cout << "Cubemap texture failed to load at path:" << tex_faces[i] << std::endl;
				stbi_image_free(data);
			}
		}

		// Reset state:
		glBindTexture(GL_TEXTURE_2D, 0);
		dirty = false;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return id;
}
