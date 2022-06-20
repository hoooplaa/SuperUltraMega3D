#pragma once

#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/Graphics/imgui_impl_glfw.h"
#include "ImGui/Graphics/imgui_impl_vulkan.h"

#include "VulkanObjects.h"

namespace Mega
{
	class Vulkan;
	
	class ImguiObject {
	public:
		friend Vulkan;
	
		void Initialize(GLFWwindow* in_pWindow);
		void Destroy(Vulkan* v);
	
		void CreateRenderData(Vulkan* v);
	
	private:
		void CreateDescriptorPool(Vulkan* v);
		void CreateFrameData(Vulkan* v);
	
		GLFWwindow* m_pWindow = nullptr;
	
		std::vector<ImGui_ImplVulkanH_Frame> m_frames;
	
		VkDescriptorPool m_descriptorPool;
	
		VkRenderPass m_renderPass;
		VkPipeline m_pipeline;
	
		VkShaderModule m_vertShaderModule;
		VkShaderModule m_fragShaderModule;
	
		std::vector<VkCommandBuffer> m_commandBuffers;
		std::vector<VkCommandPool> m_commandPools;
	};
}