#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
GLuint Texture::GetId() {

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
