#pragma once
#include "glm.hpp"

class Particle
{
public:
	Particle(const glm::vec3& _position, glm::vec3 _velocity, float _gravity_val, float _lifeTimeS, unsigned int _id)
	: m_position(_position),
	  m_velocity(_velocity),
	  m_gravityVal(_gravity_val),
	  m_timeElapsed(0.0f),
	  m_lifeTimeS(_lifeTimeS),
	  m_id(_id),
	  m_posOrigin(_position)
	{
		
	}

	bool Update(double _deltaTime);
	
	glm::vec3 GetPosition() const { return m_position; }

private:
	glm::vec3 m_posOrigin;
	glm::vec3 m_position;

	glm::vec3 m_velocity;
	
	float m_gravityVal;
	float m_timeElapsed;
	float m_lifeTimeS;

	unsigned int m_id;
	
};

