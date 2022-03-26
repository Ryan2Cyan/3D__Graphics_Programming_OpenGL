#include "Gp.h"
#include <memory>
#include <GL/glew.h>

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

}


