#pragma once
#include <memory>
#include "PhContext.h"

namespace Ph {

	std::shared_ptr<PhContext> CreateContext();
}