#include <windows.h>

#include "Game.h"

// Questions:
// - What does he mean by this: "This is an optional parameter that allows you to specify callbacks for a custom memory allocator. We will ignore this parameter in the tutorial and always pass nullptr as argument."
// - Whats the point of const char** in the init function?
//
// Shit to do:
//
// - Make a function to rate physical devices
// - Add system to control what type of messages come out
// - Learn present modes better
// - Learn render passes better
// - Fix get direction return value
// - Read that article
// - Allocate one buffer and use it for all vertex, index, etc buffers using offset 
// - LoadTexture not always breaking when wrong path is added
// - Passing things directly to frag shaders?
// - Include file types when loading in data
// - Not breaking when cant find texture path/load texture
// - Why does c++ forbid containers filled with const elements
// - 1476 have vulkan's push constant be the same types as the models, or the other way
// - Decide if bodies need a pointer to scene scene.cpp AddRigidBody() / nvm they do because if the scene has a shared ptr to it it needs to auto be removed in Body::Destroy()
// - Match physics step with game loop
// - Somehow use bullet 3d's ability to return a indentity matrix
// - Fix GetMotionStateRotation(), so much copying, return Vec3 not btVec3
// - Fix calculate inertia
// - Fix HasCollidedWith(), should rigid body have a copy of scene
// - Fix bad weak pointer when with renderer->DrawFrame(shared_from_this()) in scene
// - Maybe make the vector of Models to draw an array thats already the size of DRAW_LIMIT
// - Have guis or over the top drawing use a different pipeline so u can have low graphics in the game and high in guis
// - Make an actuall text system that stores different texts and could have a different descriptor or just better code
// - Make number of framebuffers/swapchain images/image views more centralized
// - Maybe ImGui::GetDrawData() is a big func, calling it to see if we need to draw
// - Maybe have non mutable vertex and index data use same buffer https://community.khronos.org/t/memory-management-one-buffer/7012/2
// - Rotation everything every frame maybe not the best
// - Animation players using different rects
//  - What the cherno said make renderer more broad and a level of interface in between renderer and vulkan instance (in early game engine series)
//  - window class
//  - Maybe have that class in between renderer and vulkan instance be able to create pipelines and other vulkan objects easier
//  - Fix imgui headers and includes
//  - do fancy c++ magic to fix loading models
// 
// Notes:
//
// - Did not add sfml dlls to includes in project props

int main() {
	// HWND hWnd = GetConsoleWindow();
	// ShowWindow(hWnd, SW_HIDE);

	std::shared_ptr<Game> game = std::make_shared<Game>();
	
	game->Initialize();
	
	try {
		game->Run();
	}
	catch (const std::exception& error) {
		std::cerr << error.what() << std::endl;
		EXIT_FAILURE;
	}
	
	game->Destroy();
	
	EXIT_SUCCESS;
}