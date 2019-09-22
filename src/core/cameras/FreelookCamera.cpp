#include "FreelookCamera.h"
#include "core/InputHandler.h"

#include <glm/ext/matrix_transform.hpp>

#include <iostream>

FreelookCamera::FreelookCamera(float sensitivity, float speed) :
	m_direction(glm::vec3(0.f, 0.f, -1.f)),
	m_yaw(0),
	m_pitch(0),
	m_sensitivity(sensitivity),
	m_speed(speed)
{
	setTarget(m_direction);
}

void FreelookCamera::setSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}

float FreelookCamera::sensitivity() const
{
	return m_sensitivity;
}

void FreelookCamera::handleInput(const InputHandler& inputHandler, float elapsedTime)
{
	// Move direction
	glm::vec3 movement(0);

	if (inputHandler.key(GLFW_KEY_W) == InputHandler::KeyState::HOLD)
		movement += (m_direction * m_speed * elapsedTime);
	if (inputHandler.key(GLFW_KEY_S) == InputHandler::KeyState::HOLD)
		movement += (-m_direction * m_speed * elapsedTime);

	// Strafe
	const glm::vec3 right = glm::cross(m_direction, glm::vec3(0, 1, 0));
	if (inputHandler.key(GLFW_KEY_A) == InputHandler::KeyState::HOLD)
		movement += (-right * m_speed * elapsedTime);
	if (inputHandler.key(GLFW_KEY_D) == InputHandler::KeyState::HOLD)
		movement += (right * m_speed * elapsedTime);

	// Up down
	if (inputHandler.key(GLFW_KEY_SPACE) == InputHandler::KeyState::HOLD)
		movement += (glm::vec3(0, 1, 0) * m_speed * elapsedTime);

	if (inputHandler.key(GLFW_KEY_LEFT_SHIFT) == InputHandler::KeyState::HOLD)
		movement += (-glm::vec3(0, 1, 0) * m_speed * elapsedTime);

	if (inputHandler.key(GLFW_KEY_LEFT_CONTROL) == InputHandler::KeyState::HOLD)
		movement *= 30.f;

	move(movement);

	// Look direction
	if (inputHandler.key(GLFW_KEY_UP) == InputHandler::KeyState::HOLD)
		m_pitch += m_sensitivity * elapsedTime;
	if (inputHandler.key(GLFW_KEY_DOWN) == InputHandler::KeyState::HOLD)
		m_pitch -= m_sensitivity * elapsedTime;
	if (inputHandler.key(GLFW_KEY_LEFT) == InputHandler::KeyState::HOLD)
		m_yaw -= m_sensitivity * elapsedTime;
	if (inputHandler.key(GLFW_KEY_RIGHT) == InputHandler::KeyState::HOLD)
		m_yaw += m_sensitivity * elapsedTime;

	//m_pitch = glm::clamp(m_pitch, -89.f, 89.f);

	inputHandler.grabCursor(true);
	double x, y;
	inputHandler.cursorPos(x, y);
	inputHandler.setCursorPos(0, 0);

	// Can't get mouse to work because it keeps going out of screen
	constexpr float cursorModifier = 200.f;
	m_yaw += x * m_sensitivity / cursorModifier;
	m_pitch -= y * m_sensitivity / cursorModifier;
	m_pitch = glm::clamp(m_pitch, -89.f, 89.f);

	//std::printf("Cursor pos x: %.2f y: %.2f\n", x, y);

	m_direction = glm::normalize(glm::vec3(
		glm::cos(glm::radians(m_pitch)) * glm::sin(glm::radians(m_yaw)),
		glm::sin(glm::radians(m_pitch)),
		-glm::cos(glm::radians(m_pitch)) * glm::cos(glm::radians(m_yaw))));

	setTarget(pos() + m_direction);
}