#pragma once

#include "Camera.h"

class FreelookCamera : public Camera
{
public:
	FreelookCamera(float sensitivity, float speed = 3.f);

	void setSensitivity(float sensitivity);
	float sensitivity() const;

	virtual void handleInput(const InputHandler& inputHandler, float elapsedTime) override final;

private:
	glm::vec2 m_mousePos;
	glm::vec3 m_direction;

	float m_yaw;
	float m_pitch;
	float m_sensitivity;
	float m_speed;
};