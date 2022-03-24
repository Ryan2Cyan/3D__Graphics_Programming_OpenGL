#pragma once
#include "debug.h"
#include "buffer.h"
#include <memory>
#include <GL/glew.h>


struct Buffer;

struct  GpContext
{

	void ShowDebugWindow();
	void ShowDebugWindow(bool* toggle);
	void RenderTriangle();

	std::shared_ptr<Buffer> CreateBuffer();

	// Getters:
	Debug GetDebug();

	std::weak_ptr<GpContext> self;

private:
	Debug Debug;
	bool show_debug_window = true;
};