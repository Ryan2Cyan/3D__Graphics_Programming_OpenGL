#pragma once
#include <memory>
#include "PhContext.h"
#include "PhysicsWorld.h"

namespace Ph {

	std::shared_ptr<PhContext> CreateContext();
}