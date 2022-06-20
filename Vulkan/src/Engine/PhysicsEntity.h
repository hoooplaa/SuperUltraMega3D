#pragma once

#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Engine/Physics/RigidBody.h"
#include "Engine/Core/Math/Vec.h"

namespace Mega
{
	class PhysicsEntity : public Entity {
	public:
		PhysicsEntity();
		~PhysicsEntity();
		void Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const ConstructInfoCollisionShape* in_colBoxInfo, Scene* in_pScene);
		void Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const std::vector<ConstructInfoCollisionShape*>& in_colBoxInfos, Scene* in_pScene);
		void Destroy();

		virtual void RunFrame();
		virtual void Render(const std::shared_ptr<Scene> in_scene);

		Vec3F GetBodyPosition() const;
		Vec3F GetBodyRotation() const;

	private:
		std::shared_ptr<RigidBody3D> m_rigidBody = std::make_shared<RigidBody3D>();
	};
}