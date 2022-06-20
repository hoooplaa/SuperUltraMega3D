#pragma once

#include <memory>
#include <vector>

#include <Bullet3D/LinearMath/btScalar.h>
#include <Bullet3D/LinearMath/btVector3.h>
#include <Bullet3D/LinearMath/btMatrix3x3.h>

#include "Engine/Core/Math/Vec.h"

class btRigidBody;
class btDefaultMotionState;
class btCompoundShape;
namespace Mega
{
	class Scene;
	class RigidBody3D;
}

namespace Mega
{
	// ================ CONSTRUCT INFO ==================== //
	struct ConstructInfoRigidBody3D {
		using btVec3 = btVector3;

		btVec3 globalPosition = { 0.0, 0.0, 0.0 };
		btVec3 rotation = { 0.0, 0.0, 0.0 };

		btScalar mass = 1.0;
		btScalar friction = 0.5;
		btScalar restitution = 0.5;
	};
	struct ConstructInfoCollisionShape {
		using btVec3 = btVector3;

		virtual void AddToCompoundShape(RigidBody3D* in_pBody) const { assert(false && "This shouldn't be called"); }
	};
	struct ConstructInfoCollisionBox : public ConstructInfoCollisionShape {
		using btVec3 = btVector3;

		void AddToCompoundShape(RigidBody3D* in_pBody) const;

		btVec3 localPosition = { 0.0, 0.0, 0.0 };
		btVec3 rotation = { 0.0, 0.0, 0.0 };

		btVec3 dimensions = { 1.0, 1.0, 1.0 };
	};
	struct ConstructInfoCollisionSphere : public ConstructInfoCollisionShape {
		void AddToCompoundShape(RigidBody3D* in_pBody) const;

		btVec3 localPosition = { 0.0, 0.0, 0.0 };
		btVec3 rotation = { 0.0, 0.0, 0.0 };

		btScalar radius = 1.0;
	};

	// ================== RIGID BODY 3D ================ //
	class RigidBody3D {
	public:
		friend ConstructInfoCollisionShape;
		friend ConstructInfoCollisionBox;
		friend ConstructInfoCollisionSphere;

		using btVec3 = btVector3;
		using btMat3 = btMatrix3x3;

		void Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const ConstructInfoCollisionShape* in_pColBoxInfo);
		void Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const std::vector<ConstructInfoCollisionShape*>& in_colBoxInfos);
		void Destroy();

		void Update(const float in_dt);

		void ApplyLinearForce(const btVec3& in_force);
		void ApplyLinearImpulse(const btVec3& in_force);
		void ApplyRotationalForce(const btVec3& in_force);

		btRigidBody* GetRawRigidBody() const { return m_pRigidBody; }
		Vec3F GetBodyPosition() const;
		Vec3F GetMotionStateRotation() const;
		Vec3F GetMotionStatePosition() const;
		void SetPosition(const btVec3& in_position);

	private:
		void SetupBulletRigidBody(const ConstructInfoRigidBody3D& in_info);

		btRigidBody* m_pRigidBody = nullptr;
		btDefaultMotionState* m_pMotionState = nullptr;
		btCompoundShape* m_pCompoundShape = nullptr;
	};
}