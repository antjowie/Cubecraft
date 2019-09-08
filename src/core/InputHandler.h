#pragma once

#include <GLFW/glfw3.h>

// Manages input. This class can be abstracted but that is not needed yet
class InputHandler
{
public:
	enum class KeyState;
	
	InputHandler(GLFWwindow& windowHandle);

	KeyState key(int key) const;
	KeyState button(int button) const;
	
	// Upper left in screen coordinates
	void cursorPos(double& x, double& y) const;
	void setCursorPos(double x, double y) const;
	void grabCursor(bool grab) const;

	enum class KeyState
	{
		HOLD,
		RELEASE
	};

private:
	
	static KeyState convertGLFWState(int state);

	GLFWwindow& m_windowHandle;
};