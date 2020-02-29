#include "PlayerTank.h"

#include "Obj.h"
#include "GameManager.h"

#include <fmod.h>
#include <fmod.hpp>
#include <corecrt_math.h>

PlayerTank::PlayerTank(std::string path, Shader* shader, std::vector<Boid>* _boidObjects, TextLabel* _scoreText, FMOD::System* _audioSystem, FMOD::Sound* _yeatSound, FMOD::Sound* _shoopSound) : Model(path, shader)
{
	inputManager = &(InputManager::getInstance());
	ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f);

	m_boidObjects = _boidObjects;
	m_scoreText = _scoreText;
	m_audioSystem = _audioSystem;
	m_yeatSound = _yeatSound;
	m_shoopSound = _shoopSound;
}

void PlayerTank::Update(unsigned int& _score, float _deltaTime)
{
	ProcessInput(_deltaTime);
	LookAtMouse();

	//Do head collision checks
	for (auto boidIt = m_boidObjects->begin(); boidIt != m_boidObjects->end();)
	{
		//Find distance to current boid
		const double distanceX = boidIt->GetPosition().x - m_position.x;
		const double distanceZ = boidIt->GetPosition().z - m_position.z;
		const double boidDist = sqrt(distanceX * distanceX + distanceZ * distanceZ);

		if (boidDist < boidIt->GetRadius() + m_collisionRadius)
		{
			//tank and current boid are colliding
			//Erase boid
			boidIt = m_boidObjects->erase(boidIt);

			//Update score text
			if (_score != 0)
			{
				std::string tempScore = "Score: ";
				tempScore = tempScore + std::to_string(--_score);
				m_scoreText->SetText(tempScore);
			}
			

			//Play sound
			const FMOD_RESULT play = m_audioSystem->playSound(m_yeatSound, 0, false, 0);
			if (play != FMOD_OK)
			{
				std::cout << "Failed to play sound: Thump.wav" << std::endl;
			}
		}
		else
		{
			//Only move the iterator forward if nothing was erased
			//Because it is automatically moved forward after erase() is called
			++boidIt;
		}
	}
}

void PlayerTank::ProcessInput(float _deltaTime)
{
	if (!inputManager->CAMERA_FREEEVIEW_MODE)
	{
		//Move the camera forward with the w button
		if (inputManager->KeyState['w'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['w'] == inputManager->INPUT_DOWN ||
			inputManager->KeyState['W'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['W'] == inputManager->INPUT_DOWN)
		{
			//move player tank right
			ChangePRS(-1.0f * _deltaTime, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}

		//Move the camera to the left with the a button
		if (inputManager->KeyState['a'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['a'] == inputManager->INPUT_DOWN ||
			inputManager->KeyState['A'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['A'] == inputManager->INPUT_DOWN)
		{
			//move player tank left
			ChangePRS(0.0f, 0.0f, 1.0f * _deltaTime, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		//Move the camera backwards with the s button
		if (inputManager->KeyState['s'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['s'] == inputManager->INPUT_DOWN ||
			inputManager->KeyState['S'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['S'] == inputManager->INPUT_DOWN)
		{
			//move player tank backward
			ChangePRS(1.0f * _deltaTime, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		//Move the camera to the right witht the d button
		if (inputManager->KeyState['d'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['d'] == inputManager->INPUT_DOWN ||
			inputManager->KeyState['D'] == inputManager->INPUT_DOWN_FIRST || inputManager->KeyState['D'] == inputManager->INPUT_DOWN)
		{
			//move player tank right
			ChangePRS(0.0f, 0.0f, -1.0f * _deltaTime, 0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
}

void PlayerTank::LookAtMouse()
{
	if (!inputManager->CAMERA_FREEEVIEW_MODE)
	{
		float frustumLeftSide = 4200;
		float frustumRightSide = -4200;
		float frustumTopSide = 2340;
		float frustumBottomSide = -2340;

		float z = (int)(Utils::remap(inputManager->g_mousePosX, -inputManager->HSCREEN_WIDTH, inputManager->HSCREEN_WIDTH, frustumLeftSide, frustumRightSide));
		float x = (int)(Utils::remap(inputManager->g_mousePosY, -inputManager->HSCREEN_HEIGHT, inputManager->HSCREEN_HEIGHT, frustumBottomSide, frustumTopSide));

		float vecX = x - -m_position.x;
		float vecZ = z - m_position.z;

		//Update model matrix so the boid faces in the direction it is moving
		SetPRS(m_position.x, m_position.z, glm::degrees(std::atan2(vecZ, vecX)) + 90.0f, 50.0f, 50.0f, 50.0f);
	}
}
