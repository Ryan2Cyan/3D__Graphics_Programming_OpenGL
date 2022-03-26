#include "Gp.h"
#include <memory>
#include <GL/glew.h>
#include <ext.hpp>

namespace Gp {

	// Creates a Gp context:
	std::shared_ptr<GpContext> CreateContext() {

		std::shared_ptr<GpContext> rtn = std::make_shared<GpContext>();
		if (glewInit() != GLEW_OK) {
			throw std::exception("Failed to initialise glew.");
			return NULL;
		}

		rtn->self = rtn;

		return rtn;
	}

	// Renders the scene:
	void RenderScene(int w, int h, glm::vec4 bg_col) {

		// Rendering:
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glViewport(0, 0, w, h);
		glClearColor(bg_col.x * bg_col.w, bg_col.y * bg_col.w, bg_col.z * bg_col.w, bg_col.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind texture:
		glBindTexture(GL_TEXTURE_2D, texture->GetId());

		// Bind VAO:
		glBindVertexArray(image->GetId());

		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(shader->GetId());


		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Reset the state:
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		SDL_GL_SwapWindow(window);
	}
}


