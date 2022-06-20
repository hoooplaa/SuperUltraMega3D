#pragma once

#include <array>

#include "Engine/Graphics/Vulkan/VulkanDefines.h"
#include "Engine/Core/Math/Math.h"

struct VkVertexInputBindingDescription;
struct VkVertexInputAttributeDescription;

namespace Mega
{
	struct Vertex {
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec2 texCoord = { 0.0f, 0.0f };
		glm::vec3 normal = { 0.0f, 0.0f, 1.0f };

		static VkVertexInputBindingDescription GetBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 4> GetAttributeDescriptions();

		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color && texCoord == other.texCoord && normal == other.normal;
		}
	};

	struct AnimatedVertex {
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		glm::vec3 normal = { 0.0f, 0.0f, 1.0f };
		glm::vec2 texCoord = { 0.0f, 0.0f };

		glm::vec3 tangent = { 0.0f, 0.0f, 0.0f };
		glm::vec3 biTangent = { 0.0f, 0.0f, 0.0f };

		int boneIDs[MAX_BONE_INFLUENCE];
		float weights[MAX_BONE_INFLUENCE];

		static VkVertexInputBindingDescription GetBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 4> GetAttributeDescriptions();

		bool operator==(const AnimatedVertex& other) const {
			return pos == other.pos && normal == other.normal && texCoord == other.texCoord && tangent == other.tangent && biTangent == other.biTangent;
		}
	};
}
