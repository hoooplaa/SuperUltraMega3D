#pragma once

#include "Engine/Graphics/Objects/ModelData.h"
#include "Engine/Core/Math/Math.h"

#define GLM_FORCE_RADIANS

namespace Mega
{
	class Model {
	public:
		Model();
		Model(const VertexData& in_vData);
		Model(const VertexData& in_vData, const TextureData& in_tData);

		void SetVertexData(VertexData in_data) { m_vertexData = in_data; }
		void SetTextureData(TextureData in_data) { m_textureData = in_data; }

		Vec3F GetPosition() const { return m_position; }
		Vec3F GetRotation() const { return m_rotation; }
		Vec3F GetScale()    const { return m_scale; }

		void SetPosition(const Vec3F& in_position) { m_position = in_position; }
		void SetRotation(const Vec3F& in_rotation) { m_rotation = in_rotation; }

		void SetScale(const Vec3F& in_scale) { m_scale = in_scale; }
		void SetColor(const Vec4F& in_color) { m_color = in_color; }
		void SetColor(const Vec3F& in_color) { m_color = Vec4F(in_color.x, in_color.y, in_color.z, 1.0f); }

		void SetTileSize(const Vec2F& in_dim) { m_tileSize = in_dim; }
		void SetTileTexCoords(const Vec2F& in_coords) { m_texCoords = in_coords; }

		struct PushConstant {
			Mat4x4F model = Mat4x4F(1.0f);
			Vec4F color = Vec4F(1.0f);

			Vec2F texCoordAdd = Vec2F(0.0f, 0.0f);
			Vec2F texCoordMult = Vec2F(1.0f, 1.0f);

			int32_t textureData = -1;
		};

	private:
		Vec3F m_scale = Vec3F(1.0f, 1.0f, 1.0f);
		Vec3F m_rotation = Vec3F(0.0f, 0.0f, 0.0f);
		Vec3F m_position = Vec3F(0.0f, 0.0f, 0.0f);
		Mat4x4F m_transform = Mat4x4F(1.0f);

		Vec4F m_color = Vec4F(1.0f);

		Vec2F m_tileSize = Vec2F(1.0f);
		Vec2F m_texCoords = Vec2F(0.0f, 0.0f);

		TextureData m_textureData;
		VertexData  m_vertexData;

	public:
		void GetPushConstantData(Model::PushConstant* in_pData) const;

		const TextureData* GetTextureData() const { return &m_textureData; }
		const VertexData* GetVertexData() const { return &m_vertexData; }
	};
}