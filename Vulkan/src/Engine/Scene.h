#pragma once

#include <memory>

#include <Bullet3D/btBulletCollisionCommon.h>
#include <Bullet3D/btBulletDynamicsCommon.h>

#include "Engine/Core/SystemGuard.h"
#include "Engine/Physics/RigidBody.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Objects/ModelData.h"

#define SCENE_DRAW_LIMIT_MODELS uint32_t(100)
#define SCENE_DRAW_LIMIT_SHAPES uint32_t(100)

struct GLFWwindow;
namespace Mega
{
	class Engine;
	class Renderer;
	class Camera;
	class Model;
	struct Light;
}

namespace Mega
{
	class Scene : public SystemGuard, std::enable_shared_from_this<Scene> {
	public:
		friend Engine;
		friend Renderer;

		void OnInitialize() override;
		void OnDestroy() override;

		void Update(const float in_dt);

		void Clear();
		void AddModel(Model* in_pModel);
		void AddLight(Light* in_pLight);
		void Display(const Camera& in_camera);
		void Display();

		void AddRigidBody(std::shared_ptr<RigidBody3D> in_body);

		VertexData LoadOBJ(const char* in_filePath) { return m_pRenderer->LoadOBJ(in_filePath); }
		TextureData LoadTexture(const char* in_filePath) { return m_pRenderer->LoadTexture(in_filePath); }

	private:
		void SetRenderer(Renderer* in_pRenderer) { m_pRenderer = in_pRenderer; }
		std::vector<Model*>& GetModelDrawList() { return m_pModelDrawList; }
		std::vector<Light*>& GetLightDrawList() { return m_pLightDrawList; }

		// Graphics
		Renderer* m_pRenderer = nullptr;

		std::vector<Model*> m_pModelDrawList;
		std::vector<Light*> m_pLightDrawList;

		// Physics
		btDiscreteDynamicsWorld* m_pPhysicsWorld; // Basically a container for rigid bodies
		std::vector<std::shared_ptr<RigidBody3D>> m_rigidBodies;

		btDefaultCollisionConfiguration* m_collisionConfiguration;
		btCollisionDispatcher* m_dispatcher;
		btBroadphaseInterface* m_overlappingPairCache;
		btSequentialImpulseConstraintSolver* m_solver;
	};
}