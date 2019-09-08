#include "InputHandler.h"
#include "utils/Logger.h"

InputHandler::InputHandler(GLFWwindow& windowHandle) :
	m_windowHandle(windowHandle)
{
}

InputHandler::KeyState InputHandler::key(int key) const
{
	int state = glfwGetKey(&m_windowHandle, key);
	
	return convertGLFWState(state);
}

InputHandler::KeyState InputHandler::button(int button) const
{
	int state = glfwGetMouseButton(&m_windowHandle, button);

	return convertGLFWState(state);
}

void InputHandler::cursorPos(double& x, double& y) const
{
	glfwGetCursorPos(&m_windowHandle, &x, &y);
}

void InputHandler::setCursorPos(double x, double y) const
{
	glfwSetCursorPos(&m_windowHandle, x, y);
}

void InputHandler::grabCursor(bool grab) const
{
	glfwSetInputMode(&m_windowHandle, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

InputHandler::KeyState InputHandler::convertGLFWState(int state)
{
	switch (state)
	{
	case GLFW_PRESS:
		return KeyState::PRESS;
		break;

	case GLFW_REPEAT:
		return KeyState::HOLD;
		break;

	case GLFW_RELEASE:
		return KeyState::RELEASE;
		break;

	default:
		std::string message{ "Invalid state returned by GLFW " };
		message += state;
		LOG(message, Logger::Severity::WARNING);
	}
}
