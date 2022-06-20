#pragma once

#include "Engine/Engine.h"
#include "Engine/Entity.h"
#include "Engine/PhysicsEntity.h"
#include <ImGui/imgui.h>
#include "ImGui/Graphics/imgui_impl_glfw.h"
#include "ImGui/Graphics/imgui_impl_vulkan.h"

namespace Mega
{
	static Engine CreateEngine()
	{
		Engine out_engine;
		out_engine.Initialize();

		return out_engine;
	}

	static void DestroyEngine(Engine in_pEngine)
	{
		in_pEngine.Destroy();
	}
};