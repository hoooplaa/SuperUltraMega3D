#include "Engine.h"

#include <GLFW/glfw3.h>

#include "Engine/Scene.h"
#include "Engine/Graphics/Renderer.h"

namespace Mega
{
	void Engine::Initialize()
	{
		// Initialize GLFW and create our application window
		glfwInit();

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Telling it not to create an OpenGL context
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // For now telling GLFW we dont want the window to be resized

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		// Create and position before showing
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		m_pAppWindow = glfwCreateWindow(mode->width, mode->height, "SuperUltraMega3D", nullptr, nullptr);
		int x, y; glfwGetWindowPos(m_pAppWindow, &x, &y);
		glfwSetWindowPos(m_pAppWindow, 0, y);
		glfwShowWindow(m_pAppWindow);

		// Initialize our systems
		m_pRenderer = new Renderer;
		m_pRenderer->SetWindow(m_pAppWindow);
		m_pRenderer->Initialize();

		m_pScene = new Scene;
		m_pScene->SetRenderer(m_pRenderer);
		m_pScene->Initialize();

		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
	}

	void Engine::Destroy()
	{
		// Clenup our systems
		m_pScene->Destroy();
		m_pRenderer->Destroy();

		delete m_pScene;
		delete m_pRenderer;

		// Delete our application window
		glfwDestroyWindow(m_pAppWindow);
		glfwTerminate();
	}
}