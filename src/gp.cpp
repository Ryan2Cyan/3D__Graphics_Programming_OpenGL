#include "gp.h"
#include <memory>

std::shared_ptr<GpContext> CreateContext() {

	std::shared_ptr<GpContext> rtn = std::make_shared<GpContext>();
	if (glewInit() != GLEW_OK) { 
		throw std::exception("Failed to initialise glew."); 
	}

	rtn->self = rtn;

	return rtn;
}


