#pragma once

#include <cassert>
#include <stdexcept>

#define MEGA_ASSERT(condition, msg) assert(condition && "MEGA ASSERT: " && msg)
#define MEGA_RUNTIME_ERROR(msg) throw std::runtime_error(std::string("MEGA RUNTIME ERROR: ") + msg)

namespace Mega
{
	enum class MegaResult
	{
		MEGA_SUCCESS = 0,
		MEGA_FAILURE = -1,
	};
}