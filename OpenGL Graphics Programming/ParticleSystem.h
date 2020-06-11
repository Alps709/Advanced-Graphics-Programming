#pragma once
#include "glm.hpp"
#include <iostream>
#include <vector>

#include "Particle.h"
#include "Shader.h"
#include "Texture.h"

class ParticleSystem
{
public:
	ParticleSystem() = default;
	ParticleSystem(glm::vec3 _position, float _radius);
	~ParticleSystem();
	
	void Update(Camera& _camera, float _deltaTime);
	void Render(Camera& camera);

	void SetUseComputeShader(bool _useComputeShader);
	
private:
	bool m_useComputerShader = false;
	
	unsigned int m_NumParticles = 4000;
	
	glm::vec3 m_originalPosition;
	glm::vec3 m_position;
	
	float m_circleRadius = 5.0f;
	double m_timer = 0.0f;
	
	unsigned int m_vao, m_vbo;
	Texture* m_particleTexture;
	Shader m_particleShader;

	std::vector<Particle> m_particles;
	std::vector<glm::vec4> m_particlePositions;
};

