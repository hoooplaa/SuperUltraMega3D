#include "Model.h"

#include <iostream>

#include <GLM/gtc/matrix_transform.hpp>

namespace Mega
{
	glm::mat4x4 MakeRotationMatrixX1(float in_thetaRad) {
		glm::mat4x4 out_mat(1.0f);
		out_mat[0][0] = 1.0f;
		out_mat[1][1] = cosf(in_thetaRad);
		out_mat[1][2] = sinf(in_thetaRad);
		out_mat[2][1] = -sinf(in_thetaRad);
		out_mat[2][2] = cosf(in_thetaRad);
		out_mat[3][3] = 1.0f;
		return out_mat;
	}
	glm::mat4x4 MakeRotationMatrixY1(float in_thetaRad) {
		glm::mat4x4 out_mat(1.0f);
		out_mat[0][0] = cosf(in_thetaRad);
		out_mat[0][2] = sinf(in_thetaRad);
		out_mat[2][0] = -sinf(in_thetaRad);
		out_mat[1][1] = 1.0f;
		out_mat[2][2] = cosf(in_thetaRad);
		out_mat[3][3] = 1.0f;
		return out_mat;
	}
	glm::mat4x4 MakeRotationMatrixZ1(float in_thetaRad) {
		glm::mat4x4 out_mat(1.0f);
		out_mat[0][0] = cos(in_thetaRad);
		out_mat[0][1] = sinf(in_thetaRad);
		out_mat[1][0] = -sinf(in_thetaRad);
		out_mat[1][1] = cosf(in_thetaRad);
		out_mat[2][2] = 1.0f;
		out_mat[3][3] = 1.0f;
		return out_mat;
	}

	// ========================== Model ========================== //

	Model::Model()
	{

	}

	Model::Model(const VertexData& in_vData)
	{
		SetVertexData(in_vData);
	}

	Model::Model(const VertexData& in_vData, const TextureData& in_tData)
	{
		SetVertexData(in_vData);
		SetTextureData(in_tData);
	}

	void Model::GetPushConstantData(Model::PushConstant* in_pData) const
	{
		// Model
		in_pData->model[3][0] = m_position.x;
		in_pData->model[3][1] = m_position.y;
		in_pData->model[3][2] = m_position.z;

		in_pData->model[0][0] = m_scale.x;
		in_pData->model[1][1] = m_scale.y;
		in_pData->model[2][2] = m_scale.z;

		in_pData->model = glm::rotate(in_pData->model, m_rotation.x, Vec3F(1, 0, 0));
		in_pData->model = glm::rotate(in_pData->model, m_rotation.y, Vec3F(0, 1, 0));
		in_pData->model = glm::rotate(in_pData->model, m_rotation.z, Vec3F(0, 0, 1));

		// Color
		in_pData->color = m_color;

		// Texture
		in_pData->textureData = m_textureData.index;
	}
}