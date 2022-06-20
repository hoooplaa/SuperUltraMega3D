#include "RigidBody.h"

#include <Bullet3D/btBulletDynamicsCommon.h>

#include "Engine/Scene.h"

namespace Mega
{
	// ------------------ ConstructInfo ----------------- //
	void ConstructInfoCollisionBox::AddToCompoundShape(RigidBody3D* in_pBody) const
	{
		btBoxShape* box = new btBoxShape(dimensions / 2.0); // Gets deleted in destroy
		box->setImplicitShapeDimensions(dimensions / 2.0);

		btQuaternion rotQuaternion;
		btTransform  localTransform;

		rotQuaternion.setEuler(rotation.getY(), rotation.getX(), rotation.getZ());
		localTransform.setOrigin(localPosition);
		localTransform.setRotation(rotQuaternion);

		in_pBody->m_pCompoundShape->addChildShape(localTransform, box);
	}

	void ConstructInfoCollisionSphere::AddToCompoundShape(RigidBody3D* in_pBody) const
	{
		btSphereShape* sphere = new btSphereShape(radius); // Gets deleted in destroy
		sphere->setImplicitShapeDimensions(btVector3(radius, radius, radius));

		btQuaternion rotQuaternion;
		btTransform  localTransform;

		rotQuaternion.setEuler(rotation.getY(), rotation.getX(), rotation.getZ());
		localTransform.setOrigin(localPosition);
		localTransform.setRotation(rotQuaternion);

		in_pBody->m_pCompoundShape->addChildShape(localTransform, sphere);
	}

	// ------------------ RigidBody3D ----------------- //

	void RigidBody3D::Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const ConstructInfoCollisionShape* in_pColBoxInfo)
	{
		// Compund Collision Shape //
		m_pCompoundShape = new btCompoundShape(1);

		// Rigid Body //
		SetupBulletRigidBody(*in_pBodyInfo);

		in_pColBoxInfo->AddToCompoundShape(this); // Setup and add collision shape to compound shape
	}

	void RigidBody3D::Initialize(const ConstructInfoRigidBody3D* in_pBodyInfo, const std::vector<ConstructInfoCollisionShape*>& in_colShapes)
	{
		// Compund Collision Shape //
		m_pCompoundShape = new btCompoundShape(in_colShapes.size());

		// Rigid Body //
		SetupBulletRigidBody(*in_pBodyInfo);

		for (auto info : in_colShapes) {
			info->AddToCompoundShape(this); // Setup and add collision shape to compound shape
		}
	}

	void RigidBody3D::Destroy()
	{
		for (int i = 0; i < m_pCompoundShape->getNumChildShapes(); i++) {
			delete m_pCompoundShape->getChildShape(i);
		}

		delete m_pCompoundShape;
		delete m_pMotionState;
		delete m_pRigidBody;
	}

	void RigidBody3D::Update(const float in_dt)
	{

	}

	//void RigidBody3D::Draw(const std::shared_ptr<Scene> in_scene) {
	//
	//	// Allign positions
	//	tVector3 rotVector;
	//	btVector3 globalPos = GetMotionStatePosition();
	//	for (int i = 0; i < m_pCompoundShape->getNumChildShapes(); i++) {
	//		btCollisionShape* child = m_pCompoundShape->getChildShape(i);
	//		//btBoxShape*           shape = static_cast<btBoxShape*>(child); // not used
	//		btVector3             localPos = m_pCompoundShape->getChildTransform(i).getOrigin();
	//		btTransform           transform;
	//		btQuaternion          rotQuaternion;
	//
	//		m_pMotionState->getWorldTransform(transform);
	//		rotQuaternion = transform.getRotation();
	//
	//		rotQuaternion.getEulerZYX(rotVector.y, rotVector.x, rotVector.z);
	//
	//		m_collisionDrawShapes[i]->SetPosition(globalPos + localPos);
	//		m_collisionDrawShapes[i]->SetRotation(rotVector);
	//	}
	//	m_drawShape->SetPosition(globalPos);
	//	m_drawShape->SetRotation(rotVector);
	//
	//	// Draw shapes
	//	in_scene->Render(*m_drawShape);
	//
	//	Renderer::SetProjectionFlag(RENDERER_WIREFRAME_DRAWING);
	//	for (auto& box : m_collisionDrawShapes) {
	//		in_scene->Render(*box);
	//	}
	//	Renderer::ResetProjectionFlag(RENDERER_WIREFRAME_DRAWING);
	//}

	void RigidBody3D::ApplyLinearForce(const btVec3& in_force)
	{
		m_pRigidBody->applyCentralForce(in_force);
	}

	void RigidBody3D::ApplyLinearImpulse(const btVec3& in_force)
	{
		m_pRigidBody->applyCentralImpulse(in_force);
	}

	void RigidBody3D::ApplyRotationalForce(const btVec3& in_force)
	{
		m_pRigidBody->applyTorque(in_force);
	}

	// Checks if two bodies collided in the last world step
	//bool RigidBody3D::HasCollidedWith(const std::shared_ptr<RigidBody3D> in_body)
	//{
	//	assert(m_currentScene == in_body->m_currentScene && "ERROR: Testing collision between bodies in different scenes");
	//
	//	auto pWorld = m_currentScene->m_pPhysicsWorld;
	//	int manifoldCount = pWorld->getDispatcher()->getNumManifolds();
	//
	//	for (int i = 0; i < manifoldCount; i++)
	//	{
	//		btPersistentManifold* contactManifold = pWorld->getDispatcher()->getManifoldByIndexInternal(i);
	//		const btCollisionObject* body0 = contactManifold->getBody0();
	//		const btCollisionObject* body1 = contactManifold->getBody1();
	//
	//		if ((m_pRigidBody == body0 || in_body->m_pRigidBody == body0)
	//			&& (m_pRigidBody == body1 || in_body->m_pRigidBody == body1)) {
	//			return true;
	//		}
	//	}
	//
	//	return false;
	//}

	glm::vec3 RigidBody3D::GetBodyPosition() const
	{
		btVec3 bt = m_pRigidBody->getWorldTransform().getOrigin();

		return Vec3F(bt.getX(), bt.getY(), bt.getZ());
	}

	glm::vec3 RigidBody3D::GetMotionStatePosition() const
	{
		btTransform t;
		m_pMotionState->getWorldTransform(t);
		btVec3 bt = t.getOrigin();
		return Vec3F(bt.getX(), bt.getY(), bt.getZ());
	}

	glm::vec3 RigidBody3D::GetMotionStateRotation() const
	{
		btTransform t;
		m_pMotionState->getWorldTransform(t);

		glm::vec3 out_v;
		t.getRotation().getEulerZYX(out_v.x, out_v.y, out_v.z);

		//std::cout << out_v.x << ", " << out_v.y << ", " << out_v.z << std::endl;

		return out_v;
	}

	void RigidBody3D::SetPosition(const btVec3& in_position)
	{
		// Get new transform
		btTransform newT = m_pRigidBody->getWorldTransform();
		newT.setOrigin(in_position);

		m_pRigidBody->setWorldTransform(newT);
		m_pMotionState->setWorldTransform(newT);
	}

	void RigidBody3D::SetupBulletRigidBody(const ConstructInfoRigidBody3D& in_info)
	{
		if (m_pRigidBody != nullptr) { delete m_pRigidBody; }

		btMat3 rotMatrix;
		btVec3 inertia;
		rotMatrix.setEulerYPR(in_info.rotation.getY(), in_info.rotation.getX(), in_info.rotation.getZ());

		m_pMotionState = new btDefaultMotionState(btTransform(rotMatrix, in_info.globalPosition));

		m_pCompoundShape->calculateLocalInertia(in_info.mass, inertia);

		inertia = btVector3(0.5f, 0.5f, 0.5f);
		//std::cout << inertia.getX() << ", " << inertia.getY() << ", " << inertia.getZ() << std::endl;

		btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(in_info.mass, m_pMotionState, m_pCompoundShape, inertia);
		rigidBodyInfo.m_restitution = in_info.restitution;
		rigidBodyInfo.m_friction = in_info.friction;

		m_pRigidBody = new btRigidBody(rigidBodyInfo);
	}
}