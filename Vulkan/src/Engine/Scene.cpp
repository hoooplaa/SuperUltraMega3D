#include "Scene.h"

#include <GLFW/glfw3.h>

#include "Engine/Camera.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Objects/Objects.h"

namespace Mega
{
	void Scene::OnInitialize()
	{
		MEGA_ASSERT(m_pRenderer != nullptr, "Trying to initialize scene without necesarry system Renderer; Set Renderer first");
		// Initialize Bullet 3D //
		m_collisionConfiguration = new btDefaultCollisionConfiguration();
		m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
		m_overlappingPairCache = new btDbvtBroadphase();
		m_solver = new btSequentialImpulseConstraintSolver;

		m_pPhysicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);
		m_pPhysicsWorld->setGravity(btVector3(0.0, -9.8, 0.0));
	}

	void Scene::OnDestroy()
	{
		// Cleanup Physics
		delete m_pPhysicsWorld;
		delete m_solver;
		delete m_overlappingPairCache;
		delete m_dispatcher;
		delete m_collisionConfiguration;
	}

	void Scene::Update(const float in_dt)
	{
		// Update Bullet 3D //
		m_pPhysicsWorld->stepSimulation(1.0f / 60.0f, 0);
	}

	void Scene::Clear()
	{
		m_pModelDrawList.clear();
		m_pLightDrawList.clear();
	}

	void Scene::AddModel(Model* in_pModel)
	{
		uint32_t drawCount = m_pModelDrawList.size();

		if (drawCount >= SCENE_DRAW_LIMIT_MODELS) {
			assert(false && "ERROR: Draw limit reached");

			auto index = m_pModelDrawList.begin() + (drawCount % SCENE_DRAW_LIMIT_MODELS);
			m_pModelDrawList.insert(index, in_pModel);
		}
		else {
			m_pModelDrawList.push_back(in_pModel);
		}
	}

	void Scene::AddLight(Light* in_pLight)
	{
		uint32_t lightCount = m_pLightDrawList.size();

		if (lightCount >= MAX_LIGHT_COUNT) {
			assert(false && "ERROR: Draw limit reached");

			auto index = m_pLightDrawList.begin() + (lightCount % SCENE_DRAW_LIMIT_MODELS);
			m_pLightDrawList.insert(index, in_pLight);
		}
		else {
			m_pLightDrawList.push_back(in_pLight);
		}
	}
	void Scene::Display(const Camera& in_camera)
	{
		m_pRenderer->DisplayScene(this, in_camera);
	}
	void Scene::Display()
	{
		m_pRenderer->DisplayScene(this);
	}

	void Scene::AddRigidBody(std::shared_ptr<RigidBody3D> in_body)
	{
		//assert(in_body->IsInitialized() && "ERROR: Adding an unitialized body to scene");

		m_pPhysicsWorld->addRigidBody(in_body->GetRawRigidBody());
		m_rigidBodies.push_back(in_body);
	}
}