#include "Entity.h"

namespace Mega
{
	Entity::Entity()
	{

	}

	Entity::~Entity()
	{

	}

	void Entity::Initialize()
	{

	}

	void Entity::Destroy()
	{

	}

	void Entity::RunFrame()
	{

	}

	void Entity::Render(const std::shared_ptr<Scene> in_scene)
	{
		in_scene->AddModel(&m_model);
	}

	void Entity::SetModel(Model& in_model)
	{
		m_model = in_model;
	}

	void Entity::SetModel(VertexData& in_vData, TextureData& in_tData)
	{
		m_model.SetVertexData(in_vData);
		m_model.SetTextureData(in_tData);
	}
}