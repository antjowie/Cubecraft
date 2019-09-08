#include "Game.h"
#include "utils/Logger.h"

#include <GLFW/glfw3.h>

#include <iostream>


void Game::handleInput(double elapsedTime)
{
	if (glfwGetKey(m_windowHandle,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_windowHandle, GLFW_TRUE);
}

void Game::update(double elapsedTime)
{
}

void Game::render()
{
	m_block.draw();
}

Game::Game(int width, int height):
	m_windowHandle(m_graphics.createWindow(width,height)),
	m_block(m_blockMesh)
{
}

void Game::run()
{
	glfwSetTime(1. / 60.);

	double totalTime = 0.;
	double elapsedTime = 0.;
	
	unsigned frames = 0;
	double elapsedFrameTime = 0.;

	glClearColor(0.4f, 0.4f, 0.8f, 1.f);
	while (!glfwWindowShouldClose(m_windowHandle))
	{
		// Time
		elapsedTime = glfwGetTime() - totalTime;
		if (elapsedTime > 1.)
			elapsedTime = 1. / 60.;
		totalTime += elapsedTime;

		// Input
		handleInput(elapsedTime);
		update(elapsedTime);
		
		// Render
		glClear(GL_COLOR_BUFFER_BIT);
		render();

		// GLFW stuff
		glfwSwapBuffers(m_windowHandle);
		glfwPollEvents();

		// Framerate
		frames++;
		elapsedFrameTime += elapsedTime;
		if (elapsedFrameTime > 1.)
		{
			char message[128];
			std::sprintf(message, "Rendered %i frames in %.2f seconds => %.2f fps \t| totalTime %.2f\n",
				frames, elapsedFrameTime, static_cast<double>(frames) / elapsedFrameTime, totalTime);
			
			LOG(message, Logger::Severity::INFO);
			
			frames = 0;
			elapsedFrameTime -= 1.;
		}
	}
}
