#include "Sampler.h"
#include "Texture.h"


// Adds texture to the sampler:
void Sampler::Add(const std::shared_ptr<Texture> arg) {
	texture = arg;
}

// Getters:
std::shared_ptr<Texture> Sampler::GetTexture() {
	return texture;
}