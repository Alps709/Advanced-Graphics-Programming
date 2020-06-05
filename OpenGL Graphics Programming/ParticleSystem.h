#pragma once
#include "glm.hpp"
#include <iostream>
#include <vector>


#include "Camera.h"
#include "Particle.h"
#include "Shader.h"
#include "Texture.h"

class ParticleSystem
{
public:
	ParticleSystem(glm::vec3 _position);
	~ParticleSystem();
	
	void Render(Camera& camera, float _deltaTime);
	std::vector<Particle> m_particles;
	std::vector<glm::vec3> m_particlePositions;
	
private:
	glm::vec3 m_position;
	unsigned int m_vao, m_vbo;
	Texture m_particleTexture;
	Shader m_particleShader;
	float m_NumParticles;
};

