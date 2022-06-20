#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Graphics/Graphics.h"
#include "Engine/Physics/Physics.h"

struct GLFWwindow;
namespace Mega
{
	class Renderer;
	class Scene;
}

namespace Mega
{
	class Engine
	{
	public:
		void Initialize();
		void Destroy();

		inline Renderer* GetRenderer() { //MEGA_ASSERT(IsInitialized(),"Engine not initialized");
			return m_pRenderer;
		}
		inline Scene* GetScene() { //MEGA_ASSERT(IsInitialized(), "Engine not initialized");
			return m_pScene;
		}
		inline GLFWwindow* GetApplicationWindow() { //MEGA_ASSERT(IsInitialized(), "Engine not initialized");
			return m_pAppWindow;
		}
	private:
		Renderer* m_pRenderer;
		Scene* m_pScene;
		GLFWwindow* m_pAppWindow;
	};
}