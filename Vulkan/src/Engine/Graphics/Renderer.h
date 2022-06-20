#pragma once

#include <memory>

#include "Engine/Graphics/Objects/ModelData.h"
#include "Engine/Camera.h"
#include "Engine/Core/SystemGuard.h"

#define SCREEN_WIDTH  uint32_t(2400)
#define SCREEN_HEIGHT uint32_t(1800)
//#define RENDERER_PARALLEL_PROJECTION uint8_t(128)
//#define RENDERER_WIREFRAME_DRAWING   uint8_t(64)

struct GLFWwindow;
namespace Mega
{
	class Engine;
	class Scene;
	class Vulkan;
}

namespace Mega
{
	class Renderer : public SystemGuard {
	public:
		friend Engine;

		void OnInitialize();
		void OnDestroy();

		void DisplayScene(Scene* in_scene);
		void DisplayScene(Scene* in_scene, const Camera& in_camera);
		VertexData LoadOBJ(const char* in_filepath);
		TextureData LoadTexture(const char* in_filepath);

	private:
		void SetWindow(GLFWwindow* in_pWindow) { m_pWindow = in_pWindow; }

		Vulkan* m_pVulkanInstance = nullptr;
		GLFWwindow* m_pWindow = nullptr;

		uint8_t m_bitFieldRenderFlags = 0;
	};
}