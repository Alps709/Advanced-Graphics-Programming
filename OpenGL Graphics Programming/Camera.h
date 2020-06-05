#pragma once
#include "gtc/matrix_transform.hpp"
#include "InputManager.h"

class GameObject;

class Camera
{
public:
	Camera(bool isFreeView = true);
	~Camera();

	glm::mat4 GetProjection() const { return m_perspectiveProjectionMat; }
	glm::mat4 GetView() const { return m_viewMat; }
	glm::mat4 GetProjView() const { return m_projViewMat; }
	
	glm::vec3 GetPosition() const { return m_camPosition; }
	glm::vec3 GetForwardVector() const { return m_camLookDir; }
	glm::vec3 GetRightVector() const { return m_camRight; }
	glm::vec3 GetUpVector() const { return glm::cross(m_camLookDir, m_camRight); }
	double GetCamSpeed() const { return m_camSpeed; }
	bool GetThirdPersonMode() const { return m_thirdPersonMode; }

	void SetPosition(glm::vec3 _newPos);
	void SetLookDirection(glm::vec3 _newLookDirection);
	void SetFreeView(bool _isOrtho);
	void SetThirdPersonGameObject(GameObject* _gameObject);
	
	void ResetView();
	void UpdateView();
	void UpdateVectors();
	void ProcessInput(double _deltaTime);

	

private:
	InputManager& inputManager = InputManager::getInstance();
	
	//Camera vectors
	glm::vec3 m_camPosition;
	glm::vec3 m_camLookDir;
	glm::vec3 m_camUp;
	glm::vec3 m_camRight;
	glm::vec3 m_worldUp;

	//Camera controls (rotation values in degrees)
	double m_camYaw;
	double m_camPitch;
	double m_camRoll;

	bool m_limitPitch = true;
	
	double m_camSpeed;
	double m_mouseSens;

	//Controls for whether the camera is focussed on an object
	bool m_thirdPersonMode = false;

	GameObject* m_thirdPersonObject = nullptr;

	float m_thirdPersonDistance = 5.0f;
	float m_thirdPersonAngleAroundObject = 0.0f;

	//Determines whether the camera can look around and move using kb/m input
	bool freeView = false;

	//Camera matrices
	glm::mat4 m_viewMat{};
	glm::mat4 m_perspectiveProjectionMat{};
	glm::mat4 m_projViewMat{};
};

