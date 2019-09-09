#pragma once

// Graphics is a system responsible for creating a window and 
// creating an OpenGL context. I do not know what kind of interface
// the client should have graphically wise, so for now it only supplies
// a handle

struct GLFWwindow;
class Graphics
{
public:
	Graphics();
	~Graphics();
	
	// Returns a nullptr if creation failed
	GLFWwindow* createWindow(int width, int height);

private:
	GLFWwindow *m_window;
};