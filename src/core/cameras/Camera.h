#pragma once

#include <glm/mat4x4.hpp>

// The camera class creates a transformation matrix that should be applied to all vertices.
// Multiply the view and a perspective (perspective or orthogonal) and pass it as a uniform to the shaders.
// Classes that inherit from Camera can specify interaction by overwriting handleInput. (this camera can function as a static one)
// All modifications revolve around pos and target, view just creates a lookat matrix, this allow us to easily define a freelook camera.
// We just modify the Euler angles, or when specifying a camera that orbits around something, just move the pos but not the target.

class InputHandler;
class Camera
{
public:
	Camera();

	virtual void handleInput(const InputHandler &inputHandler, float elapsedTime);

	void move(const glm::vec3& pos);
	void setPos(const glm::vec3& pos);
	void moveTarget(const glm::vec3& pos);
	void setTarget(const glm::vec3& pos);
	void setFOV(float degrees);
	void setAspectRatio(float aspectRatio);
	void setNearFar(const glm::vec2& nearFar);

	const glm::vec3& pos() const;
	const glm::vec3& target() const;
	float fov() const; // In degrees
	float aspectRatio() const;
	const glm::vec2& nearFar() const;

	glm::mat4 perspective() const;
	glm::mat4 orthogonal() const;
	glm::mat4 view() const;

private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec2 m_nearFar;

	float m_fov;
	float m_aspectRatio;
};