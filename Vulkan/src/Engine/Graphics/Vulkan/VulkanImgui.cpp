#include "VulkanImgui.h"
#include "Vulkan.h"

namespace Mega
{
	void ImguiObject::Initialize(GLFWwindow* in_pWindow)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForVulkan(in_pWindow, true);
	}

	void ImguiObject::Destroy(Vulkan* v)
	{

	}

	void ImguiObject::CreateRenderData(Vulkan* v)
	{
		CreateDescriptorPool(v);
		CreateFrameData(v);

		// Setup Platform/Renderer bindings
		ImGui_ImplVulkan_InitInfo initInfo = {};
		initInfo.Instance = v->m_instance;
		initInfo.PhysicalDevice = v->m_physicalDevice;
		initInfo.Device = v->m_device;
		initInfo.QueueFamily = v->m_queueFamilyIndices.graphicsFamily.value();
		initInfo.Queue = v->m_graphicsQueue;
		initInfo.PipelineCache = nullptr;
		initInfo.DescriptorPool = m_descriptorPool;
		initInfo.Allocator = nullptr;
		initInfo.MinImageCount = v->m_swapchainImageViews.size();;
		initInfo.ImageCount = v->m_swapchainImageViews.size();
		ImGui_ImplVulkan_Init(&initInfo, v->m_renderPass);

		VkCommandBuffer commandBuffer = v->BeginSingleTimeCommand(v->m_drawCommandPools[0]);
		ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
		v->EndSingleTimeCommand(v->m_drawCommandPools[0], commandBuffer);
	}

	void ImguiObject::CreateDescriptorPool(Vulkan* v)
	{
		std::vector<VkDescriptorPoolSize> poolSizes = {
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
		};

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<uint32_t>(v->m_swapchainImages.size());

		VkResult result = vkCreateDescriptorPool(v->m_device, &poolInfo, nullptr, &m_descriptorPool);
		assert(result == VK_SUCCESS && "ERROR: ImGui vkCreateDescriptorPool() did not return success");
	}

	void ImguiObject::CreateFrameData(Vulkan* v)
	{
		for (int i = 0; i < v->m_swapchainFramebuffers.size(); ++i) {
			ImGui_ImplVulkanH_Frame frame;
			m_frames.push_back(frame);

			frame.CommandBuffer = v->m_drawCommandBuffers[i];
			frame.CommandPool = v->m_drawCommandPools[i];
			frame.Framebuffer = v->m_swapchainFramebuffers[i];

			m_frames[i] = frame;
		}
	}
}