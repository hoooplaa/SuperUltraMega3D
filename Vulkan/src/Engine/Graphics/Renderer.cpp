#include "Renderer.h"

#include <iostream>
#include <cstdint>
#include <memory>

#include "Engine/Graphics/Vulkan/Vulkan.h"
#include "Engine/Camera.h"
#include "Engine/Scene.h"

namespace Mega
{
	void Renderer::OnInitialize()
	{
		MEGA_ASSERT(m_pWindow != nullptr, "Initializing Renderer without a scene; Set scene first");
		// Initialize Graphics
		std::cout << "Initializing Renderer..." << std::endl;

		m_pVulkanInstance = new Vulkan;
		m_pVulkanInstance->Initialize(this, m_pWindow);
	}

	void Renderer::OnDestroy()
	{
		// Destroy our Vulkan instance
		m_pVulkanInstance->Destroy();
		delete m_pVulkanInstance;
	}

	void Renderer::DisplayScene(Scene* in_scene) {
		const ViewData& viewData = Camera::GetConstViewData();
		m_pVulkanInstance->SetViewData(viewData);

		m_pVulkanInstance->DrawFrame(in_scene->GetModelDrawList(), in_scene->GetLightDrawList());
	}

	void Renderer::DisplayScene(Scene* in_scene, const Camera& in_camera) {
		const ViewData& viewData = in_camera.GetViewData();
		m_pVulkanInstance->SetViewData(viewData);

		m_pVulkanInstance->DrawFrame(in_scene->GetModelDrawList(), in_scene->GetLightDrawList());
	}

	VertexData Renderer::LoadOBJ(const char* in_filepath)
	{
		VertexData out_vertexData;
		m_pVulkanInstance->LoadVertexData(in_filepath, &out_vertexData);

		m_pVulkanInstance->UpdateLoadedVertexData();
		m_pVulkanInstance->UpdateLoadedIndexData();

		return out_vertexData;
	}

	TextureData Renderer::LoadTexture(const char* in_filepath)
	{
		TextureData out_textureData;
		m_pVulkanInstance->LoadTextureData(in_filepath, &out_textureData);

		m_pVulkanInstance->UpdateLoadedTextureData();

		return out_textureData;
	}
}