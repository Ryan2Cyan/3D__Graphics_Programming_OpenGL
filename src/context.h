#pragma once
#include "debug.h"
#include <memory>

struct  GpContext
{
	void ShowDebugWindow();
	void ShowDebugWindow(bool* toggle);

	// Getters:
	Debug GetDebug();

	std::weak_ptr<GpContext> self;

private:
	Debug GpDebug;
	bool show_debug_window = true;
};