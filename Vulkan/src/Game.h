#pragma once

#include <chrono>
#include <thread>
#include <memory>
#include <iostream>

#include "Engine/SuperUltraMega.h"

#define RIGID_BODY_SCALE 1.0f, 1.0f, 1.0f
#define CUBE_DIM Vec3(1, 1, 1)

enum class eFPS {
	DEFAULT,
	MAX
};

class Game {
public:
	using Vec2 = Mega::Vec2F;
	using Vec3 = Mega::Vec3F;
	using Vec4 = Mega::Vec4F;
	using Mat4 = Mega::Mat4x4F;
	using btVec3 = btVector3;

	void Initialize();
	void Destroy();

	void Run();
	void HandleEvents();
	void Update(const float in_dt);
	void Draw();

	std::shared_ptr<Mega::Entity> AddClone(Vec3 pos);
	void Esc();

	float GetFrameRate() const { return std::chrono::duration<float, std::milli>(m_targetTime).count(); }
	void  SetFrameRate(const float in_frameRate) {
		if (in_frameRate == 0.0f) { SetFrameRate(eFPS::MAX); }
		else { m_targetTime = std::chrono::milliseconds((int)(1000.0f / in_frameRate)); }
	}
	void  SetFrameRate(const eFPS& in_fpsSetting) {
		m_fpsSetting = in_fpsSetting;

		switch (m_fpsSetting) {
		case (eFPS::DEFAULT):
			m_targetTime = std::chrono::milliseconds((int)(1000.0f / 60.0f));
			break;
		case (eFPS::MAX):
			m_targetTime = std::chrono::milliseconds(0);
			std::cout << "MAXED OUT BABY" << std::endl;
			break;
		default:
			m_targetTime = std::chrono::milliseconds((int)(1000.0f / 60.0f));
			m_fpsSetting = eFPS::DEFAULT;
		}
	}

private:
	// Game
	Mega::Engine m_engine;
	Mega::Renderer* m_pRenderer;
	Mega::Scene* m_pScene;
	GLFWwindow* m_pWindow;
	Mega::Camera m_camera;

	Mega::Model m_tankBody;
	Mega::Model m_tankTurret;

	Mega::Light m_ambientLight;
	Mega::PhysicsEntity m_tankPhysicsBody;

	// Engine
	std::chrono::milliseconds m_targetTime = std::chrono::milliseconds(0);
	eFPS m_fpsSetting;
	float m_dt = 0.0f;

	Vec2 m_mousePos;
	Vec2 m_mouseFreezePos = Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	bool m_paused = false;

	bool m_inputW;
	bool m_inputA;
	bool m_inputS;
	bool m_inputD;
	bool m_inputSpace;
	bool m_inputLShift;
	bool m_inputESC;
};