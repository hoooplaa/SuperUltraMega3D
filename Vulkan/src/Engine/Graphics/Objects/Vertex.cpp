#include "Vertex.h"

#include "Engine/Graphics/Vulkan/VulkanInclude.h"

namespace Mega
{
	// ======================== VERTEX ====================== //
	VkVertexInputBindingDescription Vertex::GetBindingDescription()
	{
		VkVertexInputBindingDescription out_bindingDescription{};
		out_bindingDescription.binding = 0;
		out_bindingDescription.stride = sizeof(Vertex);
		out_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return out_bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 4> Vertex::GetAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 4> out_attributeDescriptions{};

		out_attributeDescriptions[0].binding = 0;
		out_attributeDescriptions[0].location = 0;
		out_attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[0].offset = offsetof(Vertex, pos);

		out_attributeDescriptions[1].binding = 0;
		out_attributeDescriptions[1].location = 1;
		out_attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[1].offset = offsetof(Vertex, color);

		out_attributeDescriptions[2].binding = 0;
		out_attributeDescriptions[2].location = 2;
		out_attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		out_attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		out_attributeDescriptions[3].binding = 0;
		out_attributeDescriptions[3].location = 3;
		out_attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[3].offset = offsetof(Vertex, normal);

		return out_attributeDescriptions;
	}

	// ===================== ANIMATED VERTEX ====================== //
	VkVertexInputBindingDescription AnimatedVertex::GetBindingDescription()
	{
		VkVertexInputBindingDescription out_bindingDescription{};
		out_bindingDescription.binding = 0;
		out_bindingDescription.stride = sizeof(AnimatedVertex);
		out_bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return out_bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 4> AnimatedVertex::GetAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 4> out_attributeDescriptions{};

		out_attributeDescriptions[0].binding = 0;
		out_attributeDescriptions[0].location = 0;
		out_attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[0].offset = offsetof(AnimatedVertex, pos);

		out_attributeDescriptions[1].binding = 0;
		out_attributeDescriptions[1].location = 1;
		out_attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[1].offset = offsetof(AnimatedVertex, normal);

		out_attributeDescriptions[2].binding = 0;
		out_attributeDescriptions[2].location = 2;
		out_attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		out_attributeDescriptions[2].offset = offsetof(AnimatedVertex, texCoord);

		out_attributeDescriptions[3].binding = 0;
		out_attributeDescriptions[3].location = 3;
		out_attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[3].offset = offsetof(AnimatedVertex, tangent);

		out_attributeDescriptions[3].binding = 0;
		out_attributeDescriptions[3].location = 3;
		out_attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		out_attributeDescriptions[3].offset = offsetof(AnimatedVertex, biTangent);

		out_attributeDescriptions[3].binding = 0;
		out_attributeDescriptions[3].location = 3;
		out_attributeDescriptions[3].format = VK_FORMAT_R32_SINT;
		out_attributeDescriptions[3].offset = offsetof(AnimatedVertex, boneIDs);

		out_attributeDescriptions[3].binding = 0;
		out_attributeDescriptions[3].location = 3;
		out_attributeDescriptions[3].format = VK_FORMAT_R32_SFLOAT;
		out_attributeDescriptions[3].offset = offsetof(AnimatedVertex, weights);

		return out_attributeDescriptions;
	}
}