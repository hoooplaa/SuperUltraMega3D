#pragma once

#include <cstdint>

#include "Engine/Core/Math/Vec.h"

namespace Mega
{
	enum class eModelType {
		UNTEXTURED_MODEL,
		TEXTURED_MODEL,
		TEXT
	};

	struct VertexData {
		uint32_t indices[2] = { 0, 0 };
	};

	struct TextureData {
		int32_t index = -1;
		Vec2F dimensions;
	};
}