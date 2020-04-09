#include "Camera.h"
#include "Math.h"
#include <freeglut.h>

Camera::Camera(bool isFreeView)
   :freeView(isFreeView),
	m_camPosition(glm::vec3{ 64.0f, 5.0f, 64.0f }),
	m_camLookDir(glm::vec3{0.0f, 0.0f, -1.0f}),
	m_worldUp(glm::vec3{ 0.0f, 1.0f, 0.0f }), 
	m_camYaw(-90.0f), m_camPitch(0), m_camRoll(0), m_camSpeed(0.01f), m_mouseSens(0.5f),
	m_viewMat(glm::lookAt(m_camPosition, m_camPosition + m_camLookDir, m_worldUp)),
	m_orthoProjectionMat(glm::ortho(-inputManager.HSCREEN_WIDTH, inputManager.HSCREEN_WIDTH, -inputManager.HSCREEN_HEIGHT, inputManager.HSCREEN_HEIGHT, -10000.0f, 10000.0f)),
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
	m_camLookDir = _newLookDirection;
	UpdateVectors();
	UpdateView();
}

void Camera::SetFreeView(bool isFreeView)
{
	freeView = isFreeView;
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
	m_camPitch = -90.0f;
	m_camRoll = 0.0f;
	m_camPosition = glm::vec3(0.0f, 2000.0f, 0.0f);
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
	if (freeView)
	{
		//Move the camera forward with the w button
		if (inputManager.KeyState['w'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['w'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['W'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['W'] == inputManager.INPUT_DOWN)
		{
			//move camera forward
			SetPosition(GetPosition() + GetLookDirection() * GetCamSpeed() * (float)_deltaTime);

			//Print camera m_position for debugging
			//std::cout << "Camera pos: x: " << m_camera->GetPosition().x << " y: " << m_camera->GetPosition().y << " z: " << m_camera->GetPosition().z  << std::endl;
		}
		//Move the camera to the left with the a button
		if (inputManager.KeyState['a'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['a'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['A'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['A'] == inputManager.INPUT_DOWN)
		{
			//move camera left
			SetPosition(GetPosition() - GetCamRight() * GetCamSpeed() * (float)_deltaTime);
		}
		//Move the camera backwards with the s button
		if (inputManager.KeyState['s'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['s'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['S'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['S'] == inputManager.INPUT_DOWN)
		{
			//move camera backward
			SetPosition(GetPosition() - GetLookDirection() * GetCamSpeed() * (float)_deltaTime);
		}
		//Move the camera to the right witht the d button
		if (inputManager.KeyState['d'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['d'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['D'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['D'] == inputManager.INPUT_DOWN)
		{
			//move camera right
			SetPosition(GetPosition() + GetCamRight() * GetCamSpeed() * (float)_deltaTime);
		}

		//Move the camera up with the space button
		if (inputManager.KeyState[32] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState[32] == inputManager.INPUT_DOWN)
		{
			glm::vec3 tempVec = GetPosition();
			tempVec.y += GetCamSpeed() * (float)_deltaTime;
			SetPosition(glm::vec3(tempVec));
		}
		//Move the camera down with the left shift button
		if (inputManager.SpecialKeyState[GLUT_KEY_SHIFT_L] == inputManager.INPUT_DOWN_FIRST || inputManager.SpecialKeyState[GLUT_KEY_SHIFT_L] == inputManager.INPUT_DOWN)
		{
			glm::vec3 tempVec = GetPosition();
			tempVec.y -= GetCamSpeed() * (float)_deltaTime;
			SetPosition(glm::vec3(tempVec));
		}

		float deltaYaw = (float)inputManager.g_mousePosDifX * m_mouseSens;
		float deltaPitch = (float)inputManager.g_mousePosDifY * m_mouseSens;

		m_camYaw += deltaYaw;

		//Limit the pitch between 90 and -90 degrees, so the camera can't get flipped
		if (m_limitPitch)
		{
			m_camPitch += deltaPitch;
			if (m_camPitch > 89)
			{
				m_camPitch = 89;
			}
			else if (m_camPitch < -89)
			{
				m_camPitch = -89;
			}
		}
	}

	//Update the vectors from the mouse input
	UpdateVectors();
	UpdateView();
}
