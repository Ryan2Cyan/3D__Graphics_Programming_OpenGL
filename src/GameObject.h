#pragma once
#include "Components.h"
#include <memory>
#include <vector>

struct GpContext;
struct Mesh;


struct GameObject {
	GameObject();
private:
	friend struct GpContext;
	friend struct Shader;

	std::shared_ptr<GpContext> context;
	std::vector<std::shared_ptr<Mesh>> meshes;
	Transform transform;
};