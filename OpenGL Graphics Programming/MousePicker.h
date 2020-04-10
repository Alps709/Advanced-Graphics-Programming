#pragma once

#include <glm.hpp>

class Camera;

class MousePicker
{
public:
	MousePicker() = default;

	glm::vec3 GetRay() { return m_currentRay; }

	void UpdateRay(Camera& _camera);

private:
	glm::vec3 m_currentRay;
};

