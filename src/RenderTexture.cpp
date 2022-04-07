#include "RenderTexture.h"


RenderTexture::RenderTexture(glm::ivec2 size, std::shared_ptr<VertexArray> quad) {

	this->quad = quad;
	this->size = size;
	fbo_id = 0;
	rbo_id = 0;
	id = 0;
	dirty = true;
}

RenderTexture::~RenderTexture() {
	GLuint del_id = id;
	glDeleteTextures(1, &del_id);

	del_id = fbo_id;
	glDeleteFramebuffers(1, &del_id);

	del_id = rbo_id;
	glDeleteRenderbuffers(1, &del_id);

}
// Sets dirty to true:
void RenderTexture::SetSize(glm::ivec2 arg) {
	size = arg;
	dirty = true;
}

void RenderTexture::SetTex(GLuint arg) {
	id = arg;
}

void RenderTexture::SetQuad(std::shared_ptr<VertexArray> arg) {
	quad = arg;
}

const GLuint RenderTexture::GetId() {

	if (dirty) {

		// Generate VAO:
		if (!fbo_id)
			glGenFramebuffers(1, &fbo_id);

		if (!fbo_id)
			throw std::exception("Failed to initialise framebuffer");

		glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

		// Insert texture data into framebuffer:
		if(!id)
			glGenTextures(1, &id);
		if (!id)
			throw std::exception("Failed to initialise framebuffer texture");
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Insert render buffer into framebuffer (depth and stencil testing):
		if(!rbo_id)
			glGenRenderbuffers(1, &rbo_id);
		if(!rbo_id)
			throw std::exception("Failed to initialise render buffer");
		glBindRenderbuffer(GL_RENDERBUFFER, rbo_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_id);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw std::exception("Framebuffer is not complete");

		// Reset state:
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		dirty = false;
	}

	return fbo_id;
}

const GLuint RenderTexture::GetTexId() {
	GetId();
	return id;
}

const std::shared_ptr<VertexArray> RenderTexture::GetVAO() {
	return quad;
}

const glm::ivec2 RenderTexture::GetSize() {
	return size;
}