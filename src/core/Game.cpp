#include "Game.h"
#include "cameras/FreelookCamera.h"
#include "utils/Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>



void Game::handleInput(float elapsedTime)
{
	if (glfwGetKey(m_windowHandle,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_windowHandle, GLFW_TRUE);

	m_camera->handleInput(m_inputHandler, elapsedTime);
}

void Game::update(float elapsedTime)
{
}

void Game::render()
{
	m_blockRenderer.render(m_blocks, *m_camera);
}

Game::Game(int width, int height)
	: m_windowHandle(m_graphics.createWindow(width,height))
	, m_camera(std::make_unique<FreelookCamera>(50,6))
	, m_inputHandler(*m_windowHandle)
{
	m_blocks.push_back(Block(m_blockMesh));
}

void Game::run()
{
	glfwSetTime(1. / 60.);

	double totalTime = 0.;
	float elapsedTime = 0.;
	
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

		// Update gameplay
		handleInput(elapsedTime);
		update(elapsedTime);
		
		// Render
		glClear(GL_COLOR_BUFFER_BIT);
		render();

		// GLFW stuff
		glfwSwapBuffers(m_windowHandle);
		glfwPollEvents();

		// Display framerate 
		frames++;
		elapsedFrameTime += elapsedTime;
		if (elapsedFrameTime > 1.)
		{
			char message[128];
			std::sprintf(message, "Rendered %i frames in %.2f seconds => %.2f fps \t| totalTime %.2f",
				frames, elapsedFrameTime, static_cast<double>(frames) / elapsedFrameTime, totalTime);
			
			LOG(message, Logger::Severity::INFO);
			
			std::sprintf(message, "X %.2f Y %.2f Z %.2f", m_camera->pos().x, m_camera->pos().y, m_camera->pos().z);
			LOG(message, Logger::Severity::INFO);


			frames = 0;
			elapsedFrameTime -= 1.;
		}
	}
}
