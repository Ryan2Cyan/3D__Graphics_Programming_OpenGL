#pragma once
#include <memory>


struct PhContext
{
	std::weak_ptr<PhContext> self;
};