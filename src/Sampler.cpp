#include "Sampler.h"
#include <memory>

struct GpContext;

struct Sampler {

private:
	std::shared_ptr<GpContext> context;
};