#include "PhysicsEntity.h"

namespace Mega
{
	PhysicsEntity::PhysicsEntity()
	{

	}

	PhysicsEntity::~PhysicsEntity()
	{

	}

	void PhysicsEntity::Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const std::vector<ConstructInfoCollisionShape*>& in_colBoxInfos, Scene* in_pScene)
	{
		Entity::Initialize();

		m_rigidBody->Initialize(in_pBodyInfo, in_colBoxInfos);

		in_pScene->AddRigidBody(m_rigidBody);
	}

	void PhysicsEntity::Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const ConstructInfoCollisionShape* in_colBoxInfo, Scene* in_pScene)
	{
		Entity::Initialize();

		m_rigidBody->Initialize(in_pBodyInfo, in_colBoxInfo);

		in_pScene->AddRigidBody(m_rigidBody);
	}

	void PhysicsEntity::Destroy()
	{
		m_rigidBody->Destroy();

		Entity::Destroy();
	}

	void PhysicsEntity::RunFrame()
	{
		Entity::RunFrame();

	}

	void PhysicsEntity::Render(const std::shared_ptr<Scene> in_scene)
	{
		m_model.SetPosition(GetBodyPosition());
		m_model.SetRotation(GetBodyRotation());

		Entity::Render(in_scene);
	}

	Vec3F PhysicsEntity::GetBodyPosition() const
	{
		return m_rigidBody->GetMotionStatePosition();
	}

	Vec3F PhysicsEntity::GetBodyRotation() const
	{
		return m_rigidBody->GetMotionStateRotation();
	}
}