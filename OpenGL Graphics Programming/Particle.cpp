#include "Particle.h"

#include <random>

//Generates a random float from 0 - 1
static float randomFloat()
{
	const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}


bool Particle::Update(double _deltaTime)
{
	m_velocity.y += m_gravityVal * _deltaTime;

	m_position += m_velocity;
	m_timeElapsed += _deltaTime;

	if (m_timeElapsed >= m_lifeTimeS) {
		m_position = m_posOrigin;
		m_velocity = glm::vec3(0.25 * cos(m_id * .0167) + randomFloat() * 0.25f - 0.125f, 
							   1.5f + 0.25f * randomFloat() - 0.125f, 
							   0.25 * sin(m_id * .0167) + randomFloat() * 0.25f - 0.125f);
		this->m_lifeTimeS = randomFloat() + 0.125;
		m_timeElapsed = 0.0f;
	}
}
