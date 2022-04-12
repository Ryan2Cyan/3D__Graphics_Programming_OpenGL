#include "Ph.h"

namespace Ph {

	// Create a Ph context:
	std::shared_ptr<PhContext> CreateContext() {
		// Init physics context class:
		std::shared_ptr<PhContext> rtn = std::make_shared<PhContext>();
		rtn->self = rtn;
		return rtn;
	}
}