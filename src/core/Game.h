#pragma once

#include "Graphics.h"
#include "BlockRenderer.h"
#include "InputHandler.h"

#include "cameras/Camera.h"

#include "objects/Block.h"
#include "objects/BlockMesh.h"

#include <memory>
#include <vector>

// The game class is responsible for running the game
// It is responsible for all the systems
class Camera;
class Game 
{
public:
	Game(int width, int height);

	void run();

private:
	void handleInput(float elapsedTime);
	void update(float elapsedTime);
	void render();

	GLFWwindow* m_windowHandle;
	Graphics m_graphics;

	std::unique_ptr<Camera> m_camera;
	InputHandler m_inputHandler;

	BlockRenderer m_blockRenderer;
	std::vector<Block> m_blocks;
	BlockMesh m_blockMesh;
};