#pragma once

#include "Graphics.h"

#include "objects/Block.h"
#include "objects/BlockMesh.h"

// The game class is responsible for running the game
// It is responsible for all the systems

class Game 
{
private:
	GLFWwindow * m_windowHandle;
	Graphics m_graphics;

	Block m_block;
	BlockMesh m_blockMesh;

	void handleInput(double elapsedTime);
	void update(double elapsedTime);
	void render();

public:
	Game(int width, int height);

	void run();
};