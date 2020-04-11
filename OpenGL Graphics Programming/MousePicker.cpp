#include "MousePicker.h"
#include "InputManager.h"
#include "Camera.h"
#include "Math.h"

#include <iostream>

InputManager& inputManager = InputManager::getInstance();

void MousePicker::UpdateRay(Camera& _camera)
{
	//Get normalised device co-ords
	double ndcMouseX = Math::remap(inputManager.g_mousePosX, -inputManager.GL_HSCREEN_WIDTH, inputManager.GL_HSCREEN_WIDTH, -1.0, 1.0);
	double ndcMouseY = Math::remap(inputManager.g_mousePosY, -inputManager.GL_HSCREEN_HEIGHT, inputManager.GL_HSCREEN_HEIGHT, -1.0, 1.0);

	//screen pos
	glm::vec2 normalizedScreenPos = glm::vec2(ndcMouseX, ndcMouseY);

	//screenpos to Proj Space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//Proj Space to eye space
	glm::mat4 invProjMat = glm::inverse(_camera.GetProjection());
	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//eyespace to world space
	glm::mat4 invViewMat = glm::inverse(_camera.GetView());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	m_currentRay = glm::normalize(glm::vec3(rayWorld));
}
