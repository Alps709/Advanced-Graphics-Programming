#include "Particle.h"


#include <iostream>
#include <random>

#include "Camera.h"

//Generates a random float from 0 - 1
static float randomFloat()
{
	const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}


void Particle::Update(Camera& _camera, glm::vec3 _particleSysPosition, double _deltaTime)
{
	float deltaTimeMS = static_cast<float>(_deltaTime) * 0.001f;
	m_velocity.y += m_gravityVal;

	m_position += m_velocity * deltaTimeMS;
	m_lifeTimeS -= deltaTimeMS;
	
	if (m_lifeTimeS < 0.0f) {
		m_position = _particleSysPosition;
		m_velocity = glm::vec3(5.0f * cos(m_id * deltaTimeMS) + 5.0f * randomFloat() - 2.5f,
							   20.0f + 5.0f * randomFloat() - 2.5f, 
							   5.0f * sin(m_id * deltaTimeMS) + 5.0f * randomFloat() - 2.5f);
		this->m_lifeTimeS = 0.5f + randomFloat();
	}

	m_cameraDistance = glm::distance(_camera.GetPosition(), m_position);
}
