#pragma once

#include "Engine/Core/Math/Vec.h"

namespace Mega
{
	enum class eLightTypes {
		Directional,
		Point,
		Spotlight
	};

	struct Light {
		using glScalarF = float;
		using glScalarUI = uint32_t;

		alignas(sizeof(glScalarUI)) eLightTypes type = eLightTypes::Directional;

		glScalarF constant = 1.0f;
		glScalarF linear = 0.09f;
		glScalarF quadratic = 0.032f;

		glScalarF strength = 1.0f;
		glScalarF ambient = 0.0f;
		glScalarF specular = 0.1f;

		glScalarF inCutOff = 0.9f;
		glScalarF outCutOff = 0.8f;
		glScalarF PADDING1;
		glScalarF PADDING2;

		alignas(sizeof(glScalarF) * 4)  Vec3F  position = Vec3F(0.0f, 0.0f, 0.0f);
		alignas(sizeof(glScalarF) * 4)  Vec3F  direction = Vec3F(0.0f, 0.0f, 1.0f);
		alignas(sizeof(glScalarUI) * 4) Vec3UF color = Vec3UF(1.0f, 1.0f, 1.0f);
	};
}