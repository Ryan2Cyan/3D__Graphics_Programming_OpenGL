#include "Gp.h"
#include <memory>
#include <glfw/glfw3.h>
#include <GL/glew.h>

namespace Gp {

	// Creates a Gp context:
	std::shared_ptr<GpContext> CreateContext() {

		// Init glew:
		if (glewInit() != GLEW_OK) {
			throw std::exception("Failed to initialise glew.");
			return NULL;
		}

		// Init context class:
		std::shared_ptr<GpContext> rtn = std::make_shared<GpContext>();
		rtn->self = rtn;
		return rtn;
	}

	// Returns GLFW window:
	GLFWwindow* CreateWindow(glm::vec2 resolution) {

		// Init glfw:
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow((int)resolution.x, (int)resolution.y, "3DGP Assignment 2", NULL, NULL);
		if (!window) {
			throw std::exception("Cannot initialise GLFW window");
			glfwTerminate();
		}
		return window;
	}
}


