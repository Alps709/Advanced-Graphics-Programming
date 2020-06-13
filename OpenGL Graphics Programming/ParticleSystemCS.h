#pragma once
#include "glm.hpp"
#include <iostream>
#include <vector>

#include "Particle.h"
#include "Shader.h"
#include "Texture.h"

class ParticleSystemCS
{
public:
	ParticleSystemCS() = default;
	ParticleSystemCS(glm::vec3 _position, float _radius);
	~ParticleSystemCS();

	void Update(float _deltaTime);
	void Render(Camera& camera);

private:
	unsigned int m_NumParticles = 128 * 4000;

	glm::vec3 m_originalPosition;
	glm::vec3 m_position;

	float m_circleRadius = 5.0f;
	double m_timer = 0.0f;
	
	Texture* m_particleTexture;
	Shader m_particleShader;
	Shader m_computeShader;

	std::vector<glm::vec4> m_InitialPosition;
	std::vector<glm::vec4> m_InitialVelocity;
	GLuint m_posVbo, m_velVbo, m_initVelVbo, m_particleVao;
};

