#pragma once
#include "glm.hpp"

class Camera;

class Particle
{
public:

	Particle() = default;
	
	Particle(const glm::vec3& _position, glm::vec3 _velocity, float _gravity_val, float _lifeTimeS, unsigned int _id)
	: m_position(_position),
	  m_velocity(_velocity),
	  m_gravityVal(_gravity_val),
	  m_lifeTimeS(_lifeTimeS),
	  m_id(_id)
	{
		
	}

	void Update(Camera& _camera, glm::vec3 _particleSysPosition, double _deltaTime);
	
	glm::vec3 GetPosition() const { return m_position; }
	float GetCamDistance() const { return m_cameraDistance; }

private:
	glm::vec3 m_position;

	glm::vec3 m_velocity;

	float m_cameraDistance;
	
	float m_gravityVal;
	float m_lifeTimeS;

	unsigned int m_id;
};

