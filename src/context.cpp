#include "context.h"
#include "gp.h"

// Toggle showing the debug window:
void GpContext::ShowDebugWindow() {
	GpDebug.RenderWindow();
}

void GpContext::ShowDebugWindow(bool* toggle) {
	if (toggle) { GpDebug.RenderWindow(); }
}

// Getters:
Debug GpContext::GetDebug() { return GpDebug; }