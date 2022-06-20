#include "Game.h"

#include <GLFW/glfw3.h>

imgui_addons::ImGuiFileBrowser file_dialog;

float dir[3] = { 0.0f, 0.0f, 0.0f };
float pos[3] = { 0.0f, 2.0f, 0.0f };
float speed = 0.00002f;
float col[3] = { 1.0f, 1.0f, 1.0f };

void Game::Esc() {
	m_paused = !m_paused;

	Vec2 mouseFreezePos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (m_paused) {
		glfwSetCursorPos(m_pWindow, mouseFreezePos.x, mouseFreezePos.y);
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else {
		glfwSetCursorPos(m_pWindow, mouseFreezePos.x, mouseFreezePos.y);
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CROSSHAIR_CURSOR);
	}
}

void Game::Initialize()
{
	// Initialze Graphics
	m_engine = Mega::CreateEngine();
	m_pRenderer = m_engine.GetRenderer();
	m_pScene = m_engine.GetScene();
	m_pWindow = m_engine.GetApplicationWindow();

	m_tankBody = Mega::Model(m_pRenderer->LoadOBJ("Assets/Models/wiiTankBody1.obj"));
	m_tankTurret = Mega::Model(m_pRenderer->LoadOBJ("Assets/Models/wiiTankTurret1.obj"));

	Mega::ConstructInfoRigidBody3D bodyInfo;
	Mega::ConstructInfoCollisionBox shapeInfo;
	m_tankPhysicsBody = Mega::PhysicsEntity();
	m_tankPhysicsBody.Initialize(&bodyInfo, &shapeInfo, m_pScene);
}

void Game::Destroy()
{
	m_pScene->Destroy();
}

void Game::Run()
{
	SetFrameRate(eFPS::DEFAULT);
	glfwSetCursorPos(m_pWindow, m_mouseFreezePos.x, m_mouseFreezePos.y);
	while (!glfwWindowShouldClose(m_pWindow)) {
		auto startTime = std::chrono::high_resolution_clock::now();

		HandleEvents();
		Update(m_dt);
		Draw();
		auto endTime = std::chrono::high_resolution_clock::now();

		//auto deltaTime = startTime - endTime;
		auto deltaTime = endTime - startTime;
		if (deltaTime < m_targetTime) {
			auto remainingTime = m_targetTime - deltaTime - std::chrono::milliseconds(7);
			if (remainingTime > std::chrono::milliseconds(0)) {
				std::this_thread::sleep_for(remainingTime);

				while ((std::chrono::high_resolution_clock::now() - startTime) < m_targetTime) {}
			}
		}
		m_dt = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count();
		//std::cout << m_dt << std::endl;
	}
}

void Game::HandleEvents()
{
	glfwPollEvents();

	m_inputW	  = (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS);
	m_inputA	  = (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS);
	m_inputS	  = (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS);
	m_inputD	  = (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS);
	m_inputSpace  = (glfwGetKey(m_pWindow, GLFW_KEY_SPACE) == GLFW_PRESS);
	m_inputLShift = (glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
	m_inputESC    = (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS);
}

void Game::Update(const float in_dt)
{
	if (m_inputESC) { Esc(); }

	// Camera Movement
	float cameraSpeed = 0.1f;
	float mouseSpeed = 3;

	// fix this
	if (!m_paused) {
		double x, y;
		glfwGetCursorPos(m_pWindow, &x, &y);
		m_mousePos.x = x;
		m_mousePos.y = y;
		Vec2 mouseMovement = m_mousePos - m_mouseFreezePos;
		glfwSetCursorPos(m_pWindow, m_mouseFreezePos.x, m_mouseFreezePos.y);
		
		m_camera.RotatePitch(-mouseMovement.y / 1000);
		m_camera.RotateYaw(mouseMovement.x / 1000);
		
		if (m_inputW) { m_camera.Forward(cameraSpeed);  }
		if (m_inputS) { m_camera.Forward(-cameraSpeed); }
		if (m_inputA) { m_camera.Strafe(cameraSpeed);   }
		if (m_inputD) { m_camera.Strafe(-cameraSpeed);  }
		if (m_inputSpace)  { m_camera.Up(cameraSpeed);  }
		if (m_inputLShift) { m_camera.Up(-cameraSpeed); }

	}

	// Update
	m_pScene->Update(in_dt);
}	

void Game::Draw()
{
	// =================== ImGui =================== //
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	/*
	* bool open = false, save = false;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Open", NULL))
				open = true;
			if (ImGui::MenuItem("Save", NULL))
				save = true;

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	//Remember the name to ImGui::OpenPopup() and showFileDialog() must be same...
	if (open) { ImGui::OpenPopup("Open File"); }
	if (save) { ImGui::OpenPopup("Save File"); }

	// Optional third parameter. Support opening only compressed rar/zip files.
	// Opening any other file will show error, return false and won't close the dialog.
	// 
	if (file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".rar,.zip,.7z,.obj"))
	{
		std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
		std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file

		//g_vertexData = Renderer::LoadOBJ(file_dialog.selected_path.c_str());

		//g_loadedModelNames.push_back(file_dialog.selected_fn);
	}
	if (file_dialog.showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".png,.jpg,.bmp,.obj"))
	{
		std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
		std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
		std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
		//Do writing of files based on extension here selected();
	}

	for (int32_t i = 0; i < g_loadedModelNames.size(); ++i) {
		ImGui::Button(g_loadedModelNames[i].c_str(), ImVec2(300, 100));
	}

	ImGui::BulletText("Drag and drop to re-order");
	ImGui::Indent();
	static const char* names[6] = { "1. Adbul", "2. Alfonso", "3. Aline", "4. Amelie", "5. Anna", "6. Arthur" };
	int move_from = -1, move_to = -1;
	for (int n = 0; n < IM_ARRAYSIZE(names); n++)
	{
		ImGui::Selectable(names[n]);

		ImGuiDragDropFlags src_flags = 0;
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
		//src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
		if (ImGui::BeginDragDropSource(src_flags))
		{
			if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
				ImGui::Text("Moving \"%s\"", names[n]);
			ImGui::SetDragDropPayload("DND_DEMO_NAME", &n, sizeof(int));
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			ImGuiDragDropFlags target_flags = 0;
			target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
			target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_NAME", target_flags))
			{
				move_from = *(const int*)payload->Data;
				move_to = n;
			}
			ImGui::EndDragDropTarget();
		}
	}

	if (move_from != -1 && move_to != -1)
	{
		// Reorder items
		int copy_dst = (move_from < move_to) ? move_from : move_to + 1;
		int copy_src = (move_from < move_to) ? move_from + 1 : move_to;
		int copy_count = (move_from < move_to) ? move_to - move_from : move_from - move_to;
		const char* tmp = names[move_from];
		//printf("[%05d] move %d->%d (copy %d..%d to %d..%d)\n", ImGui::GetFrameCount(), move_from, move_to, copy_src, copy_src + copy_count - 1, copy_dst, copy_dst + copy_count - 1);
		memmove(&names[copy_dst], &names[copy_src], (size_t)copy_count * sizeof(const char*));
		names[move_to] = tmp;
		ImGui::SetDragDropPayload("DND_DEMO_NAME", &move_to, sizeof(int)); // Update payload immediately so on the next frame if we move the mouse to an earlier item our index payload will be correct. This is odd and showcase how the DnD api isn't best presented in this example.
	}
	ImGui::Unindent();
	*/

	ImGui::SliderFloat("FPS: ", &m_dt, 1, 1000);

	ImGui::DragFloat3("Offset: ", pos, 0.01f);
	ImGui::DragFloat3("Color: ", col, 0.01f);
	m_ambientLight.color = Vec3(col[0], col[1], col[2]);
	m_ambientLight.position = Vec3(pos[0], pos[1], pos[2]);

	ImGui::SliderFloat("Speed: ", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("Albedo: ", &m_ambientLight.constant, 0.0f, 1.0f);
	ImGui::SliderFloat("Ambient: ", &m_ambientLight.ambient, 0.0f, 1.0f);
	ImGui::SliderFloat("Roughness: ", &m_ambientLight.quadratic, 0.0f, 1.0f);
	ImGui::SliderFloat("Metallic: ", &m_ambientLight.linear, 0.0f, 1.0f);
	ImGui::SliderFloat("AO: ", &m_ambientLight.specular, 0.0f, 1.0f);
	ImGui::SliderFloat("Strength: ", &m_ambientLight.strength, 0.0f, 10.0f);


	// ========================================== //

	m_pScene->Clear();

	m_pScene->AddLight(&m_ambientLight);
	m_pScene->AddModel(&m_tankBody);
	m_pScene->AddModel(&m_tankTurret);
	
	ImGui::Render();
	m_pScene->Display(m_camera);
}