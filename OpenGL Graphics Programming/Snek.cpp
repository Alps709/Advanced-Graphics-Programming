#include "Snek.h"

#include "Obj.h"
#include "GameManager.h"

#include <fmod.h>
#include <fmod.hpp>
#include <corecrt_math.h>


Snek::Snek(std::vector<Boid>* _boidObjects, TextLabel* _scoreText, FMOD::System* _audioSystem, FMOD::Sound* _yeatSound, FMOD::Sound* _shoopSound, unsigned _snekStartSize)
	: m_boidObjects(_boidObjects), m_scoreText(_scoreText), m_audioSystem(_audioSystem), m_yeatSound(_yeatSound), m_shoopSound(_shoopSound)
{
	m_snekClock.Initialise();
	
	//Set Snake body circle's mesh and texture
	//m_snekMesh = new Mesh(Objects::verticesSnekPart, Objects::indicesSnekPart);
	m_snekMesh = new SphereMesh();
	m_snekShader = new Shader("Shaders/SphereRimLightVS.glsl", "Shaders/SphereRimLightFS.glsl");
	m_snekTexture = new Texture("Resources/Textures/idk2.png", 0);

	//Create 100 snek body circle models
	for (unsigned int i = 0; i < _snekStartSize; i++)
	{
		SnekPart myTempObject = SnekPart(m_snekMesh, m_snekShader, glm::vec3(500, 0, 0));
		myTempObject.SetTexture0(m_snekTexture);
		myTempObject.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f);
		m_snekObjects.push_back(myTempObject);
	}
}

Snek::~Snek()
{
	delete m_snekMesh;
	delete m_snekShader;
	delete m_snekTexture;
}

void Snek::Render(Camera& _camera)
{
	//Iterate over it backwards so the first element (the head of the snek) is rendered on top of the others
	for (auto rIt = m_snekObjects.rbegin(); rIt != m_snekObjects.rend(); ++rIt)
	{
		rIt->Render(_camera);
	}
}

void Snek::Process(GameState& _gameState, unsigned int& _score, double _deltaTime)
{
	m_snekClock.Process();
	if(m_snekClock.GetTimeElapsedS() > 1.0/3.0)
	{
		//2 seconds have past, so delete the last snek part
		m_snekClock.ResetElaspedTime();
		if(!m_snekObjects.empty())
		{
			m_snekObjects.pop_back();
		}
		else
		{
			_gameState = GAME_OVER;
		}
	}

	int i = 0;
	glm::vec3 tempPos{ 0 };

	for (auto& snekPart : m_snekObjects)
	{
		//If its the first iteration of the loop, then this is the head of the snek
		if (i == 0)
		{
			glm::vec3 mousePos = glm::vec3(inputManager.g_mousePosX, inputManager.g_mousePosY, 0.0f);
			double mouseDistance = glm::length(mousePos - snekPart.GetPosition());
			
			//Stop the snek if it moves within 5 pixels of the mouse
			if (mouseDistance < 5)
			{
				return;
			}

			//Direction from snek part pos to mouse pos
			glm::vec3 directionVec = mousePos - snekPart.GetPosition();

			//Normalise
			directionVec = glm::normalize(directionVec);

			//Accumulate movement
			m_movement.x += directionVec.x * (float)_deltaTime;
			m_movement.y += directionVec.y * (float)_deltaTime;
			
			//Actual movement distance
			double movementDist = glm::length(m_movement);

			//If the movement spacing threshold is not met, then the snake can not move yet
			if (!(movementDist > m_snekSpeed)) return;

			//Move the head of the snek
			snekPart.ChangePRS(m_movement.x, m_movement.y, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			tempPos = snekPart.GetPosition();

			//Set these back to 0 after the accumulated movement was used
			m_movement = glm::vec2{ 0.0f, 0.0f };

			//Do head collision checks
			for (auto boidIt = m_boidObjects->begin(); boidIt != m_boidObjects->end();)
			{
				//Find distance to current boid
				const double distanceX = boidIt->GetPosition().x - snekPart.GetPosition().x;
				const double distanceY = boidIt->GetPosition().y - snekPart.GetPosition().y;
				const double boidDist = sqrt(distanceX * distanceX + distanceY * distanceY);

				
				if (boidDist < boidIt->GetRadius() + snekPart.GetRadius())
				{
					//Head of snek and current boid are colliding
					//EAT BOID
					//Erase boid
					boidIt = m_boidObjects->erase(boidIt);

					//Add a snek part
					SnekPart myTempObject = SnekPart(m_snekMesh, m_snekShader, glm::vec3(-10000, -10000, 0));
					myTempObject.SetTexture0(m_snekTexture);
					m_snekObjects.push_back(myTempObject);

					//Update score text
					std::string tempScore = "Score: ";
					tempScore = tempScore + std::to_string(++_score);
					m_scoreText->SetText(tempScore);

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
			//Increment to say it's not the first loop anymore
			i++;
		}
		else
		{	//This is not the first iteration of the loop, so it's a body section of the snek
			const glm::vec3 tempPos2 = snekPart.GetPosition();

			//Move the rest of the body
			snekPart.SetPosition(tempPos);
			tempPos = tempPos2;
		}
		i++;
	}
}

void Snek::ProcessInput()
{
}
