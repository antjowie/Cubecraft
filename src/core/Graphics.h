#pragma once

struct GLFWwindow;
class Graphics
{
private:
	GLFWwindow *m_window;

public:
	Graphics();
	~Graphics();

	GLFWwindow* createWindow(int width, int height);
};