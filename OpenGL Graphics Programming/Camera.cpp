#include "Camera.h"
#include "Math.h"
#include "GameObject.h"
#include <freeglut.h>

Camera::Camera(bool isFreeView)
   :freeView(isFreeView),
	m_camPosition(glm::vec3{ 64.0f, 10.0f, 64.0f }),
	m_camLookDir(glm::vec3{0.0f, 0.0f, -1.0f}),
	m_worldUp(glm::vec3{ 0.0f, 1.0f, 0.0f }), 
	m_camYaw(0.0), m_camPitch(0.0), m_camRoll(0.0), m_camSpeed(0.01), m_mouseSens(0.2),
	m_viewMat(glm::lookAt(m_camPosition, m_camPosition + m_camLookDir, m_worldUp)),
	m_perspectiveProjectionMat(glm::perspective(glm::radians(90.0f), 1280.0f/720.0f, 0.1f, 1000000.0f))
{
	inputManager.CAMERA_FREEEVIEW_MODE = isFreeView;
	SetFreeView(isFreeView);
	UpdateVectors();
	UpdateView();
}

Camera::~Camera()
= default;

void Camera::SetPosition(glm::vec3 _newPos)
{
	m_camPosition = _newPos;
	UpdateVectors();
	UpdateView();
}

void Camera::SetLookDirection(glm::vec3 _newLookDirection)
{
	m_camYaw = _newLookDirection.y;
	m_camPitch = _newLookDirection.x;
	UpdateVectors();
	UpdateView();
}

void Camera::SetFreeView(bool isFreeView)
{
	freeView = isFreeView;
	m_thirdPersonMode = false;
	inputManager.CAMERA_FREEEVIEW_MODE = isFreeView;

	//Reset the camera view back to default for an orthographic view
	if (isFreeView)
	{
		//Turn off cursor
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
	{
		//Turn on cursor
		glutSetCursor(GLUT_CURSOR_BOTTOM_SIDE);
		ResetView();
	}
}

void Camera::ResetView()
{
	//Change the view back to the original
	//So that it is changed back to a view that is perpendicular to the 2d plane
	m_camYaw = 0.0f;
	m_camPitch = 0.0f;
	m_camRoll = 0.0f;
	m_camPosition = glm::vec3(64.0f, 10.0f, 64.0f);

	inputManager.g_mousePosX = 0;
	inputManager.g_mousePosY = 0;
	inputManager.g_mousePosDifX = 0;
	inputManager.g_mousePosDifY = 0;

	//Update the vectors from the mouse input
	UpdateVectors();
	UpdateView();
}

void Camera::UpdateView()
{
	m_viewMat = glm::lookAt(m_camPosition, m_camPosition + m_camLookDir, m_worldUp);

	//Update the projection view matrix
	m_projViewMat = m_perspectiveProjectionMat * m_viewMat;
}

void Camera::UpdateVectors()
{
	//Update front vector
	m_camLookDir = glm::normalize
                   (
                    glm::vec3(cos(glm::radians(m_camYaw)) * cos(glm::radians(m_camPitch)), //x
                   	sin(glm::radians(m_camPitch)),										   //y
                   	sin(glm::radians(m_camYaw)) * cos(glm::radians(m_camPitch)))           //z
                   );

	//Update up and right vectors
	m_camRight = glm::normalize(glm::cross(m_camLookDir, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_camUp = glm::normalize(glm::cross(m_camRight, m_camLookDir));
}

void Camera::ProcessInput(double _deltaTime)
{
	if (inputManager.KeyState['m'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['M'] == inputManager.INPUT_DOWN_FIRST)
	{
		m_thirdPersonMode = !m_thirdPersonMode;
	}
	
	if (freeView && !m_thirdPersonMode)
	{
		//Move the camera forward with the w button
		if (inputManager.KeyState['w'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['w'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['W'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['W'] == inputManager.INPUT_DOWN)
		{
			//move camera forward
			SetPosition(GetPosition() + GetLookDirection() * (float)GetCamSpeed() * (float)_deltaTime);

			//Print camera m_position for debugging
			//std::cout << "Camera pos: x: " << m_camera->GetPosition().x << " y: " << m_camera->GetPosition().y << " z: " << m_camera->GetPosition().z  << std::endl;
		}
		//Move the camera to the left with the a button
		if (inputManager.KeyState['a'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['a'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['A'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['A'] == inputManager.INPUT_DOWN)
		{
			//move camera left
			SetPosition(GetPosition() - GetCamRight() * (float)GetCamSpeed() * (float)_deltaTime);
		}
		//Move the camera backwards with the s button
		if (inputManager.KeyState['s'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['s'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['S'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['S'] == inputManager.INPUT_DOWN)
		{
			//move camera backward
			SetPosition(GetPosition() - GetLookDirection() * (float)GetCamSpeed() * (float)_deltaTime);
		}
		//Move the camera to the right witht the d button
		if (inputManager.KeyState['d'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['d'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['D'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['D'] == inputManager.INPUT_DOWN)
		{
			//move camera right
			SetPosition(GetPosition() + GetCamRight() * (float)GetCamSpeed() * (float)_deltaTime);
		}

		//Move the camera up with the space button
		if (inputManager.KeyState[32] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState[32] == inputManager.INPUT_DOWN)
		{
			glm::vec3 tempVec = GetPosition();
			tempVec.y += (float)(GetCamSpeed() * _deltaTime);
			SetPosition(glm::vec3(tempVec));
		}
		//Move the camera down with the left shift button
		if (inputManager.SpecialKeyState[GLUT_KEY_SHIFT_L] == inputManager.INPUT_DOWN_FIRST || inputManager.SpecialKeyState[GLUT_KEY_SHIFT_L] == inputManager.INPUT_DOWN)
		{
			glm::vec3 tempVec = GetPosition();
			tempVec.y -= (float)(GetCamSpeed() * _deltaTime);
			SetPosition(glm::vec3(tempVec));
		}

		const double deltaYaw = static_cast<double>(inputManager.g_mousePosDifX) * m_mouseSens;
		const double deltaPitch = static_cast<double>(inputManager.g_mousePosDifY) * m_mouseSens; 

		//std::cout << "Change in yaw: " << deltaYaw << std::endl;
		//std::cout << "Change in pitch: " << deltaPitch << std::endl;
		//std::cout << "Mouse pos - x: " << inputManager.g_mousePosX << " | y: " << inputManager.g_mousePosY << std::endl;

		m_camYaw += deltaYaw;

		//Limit the pitch between 90 and -90 degrees, so the camera can't get flipped
		if (m_limitPitch)
		{
			m_camPitch += deltaPitch;
			if (m_camPitch > 89.99)
			{
				m_camPitch = 89.99;
			}
			else if (m_camPitch < -89.99)
			{
				m_camPitch = -89.99;
			}
		}
	}

	if(m_thirdPersonMode && freeView)
	{
		const double deltaYaw = static_cast<double>(inputManager.g_mousePosDifX) * m_mouseSens;
		const double deltaPitch = static_cast<double>(inputManager.g_mousePosDifY) * m_mouseSens;

		//std::cout << "Change in yaw: " << deltaYaw << std::endl;
		//std::cout << "Change in pitch: " << deltaPitch << std::endl;
		//std::cout << "Mouse pos - x: " << inputManager.g_mousePosX << " | y: " << inputManager.g_mousePosY << std::endl;

		m_thirdPersonAngleAroundObject -= static_cast<float>(deltaYaw) * 0.3f;

		//Limit the pitch between 90 and -90 degrees, so the camera can't get flipped
		if (m_limitPitch)
		{
			m_camPitch += deltaPitch * 0.3;
			if (m_camPitch > 89.99)
			{
				m_camPitch = 89.99;
			}
			else if (m_camPitch < -89.99)
			{
				m_camPitch = -89.99;
			}
		}

		//Calculate distance from third person target
		float horizontalDistance = m_thirdPersonDistance * cosf(static_cast<float>(glm::radians(-m_camPitch)));
		float verticalDistance   = m_thirdPersonDistance * sinf(static_cast<float>(glm::radians(-m_camPitch)));
		float theta = static_cast<float>(m_thirdPersonAngleAroundObject) + m_thirdPersonObject->GetRotationAngle();

		float offsetX = horizontalDistance * sinf(glm::radians(theta));
		float offsetZ = horizontalDistance * cosf(glm::radians(theta));

		auto tempPos = m_thirdPersonObject->GetPosition();
		
		m_camPosition.x = tempPos.x - offsetX;
		m_camPosition.y = tempPos.y + verticalDistance;
		m_camPosition.z = tempPos.z - offsetZ;

		m_camYaw = static_cast<double>(90.0f - theta);
	}

	//Update the vectors from the mouse input
	UpdateVectors();
	UpdateView();
}

void Camera::SetThirdPersonGameObject(GameObject* _gameObject)
{
	m_thirdPersonObject = _gameObject;
}
