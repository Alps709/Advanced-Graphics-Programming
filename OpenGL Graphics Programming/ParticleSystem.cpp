#include "ParticleSystem.h"

#include <algorithm>


#include "Camera.h"
#include <ctime>

//Generates a random float from 0 - 1
static float randomFloat()
{
	const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}

ParticleSystem::ParticleSystem(glm::vec3 _position, float _radius)
{
	m_particleShader = Shader("Shaders/Particle_0_VS.glsl", "Shaders/Particle_1_GS.glsl", "Shaders/Particle_2_FS.glsl");
	m_particleTexture = new Texture("Resources/Textures/Snowflake.png", 0);
	
	m_originalPosition = _position;
	m_circleRadius = _radius;
	
	//Allocate the memory for the particles and a vector of their positions used for the vbo
	m_particles.resize(m_NumParticles);
	m_particlePositions.resize(m_NumParticles);
	
	for (unsigned int i = 0; i < m_NumParticles; i++)
	{
		//initialize position vector
		Particle p = Particle(m_originalPosition,

							  //vel x
							  glm::vec3(10.0f * cos(i * .0167f) + randomFloat() * 0.25f - 0.125f,
							  //vel y
							  15.25f + 0.25f * randomFloat() - 0.125f,
							  //vel z
							10.0f * sin(i * .0167f) + randomFloat() * 0.25f - 0.125f),

                              //Gravity val 
							  -1.0f,

                              // lifetime 
							  0.125f + randomFloat(),

                              //id
							  i); 

		//Add the new particle to the vector
		m_particles[i] = p;
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	glGenVertexArrays(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_particlePositions.size(), &m_particlePositions[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(Camera& _camera, float _deltaTime)
{
	m_timer += 0.001f * _deltaTime;
	m_position = glm::vec3((m_circleRadius * sin(static_cast<float>(m_timer))) + m_originalPosition.x,
		                     m_originalPosition.y,
		                     (m_circleRadius * cos(static_cast<float>(m_timer))) + m_originalPosition.z);
	
	//Update partcles and their positions for the VBO
	for (int i = 0; i < (int)m_NumParticles; i++)
	{
		m_particles[i].Update(_camera, m_position, _deltaTime);
		m_particlePositions[i] = glm::vec4(m_particles[i].GetPosition(), 1.0f);
	}

	std::sort(m_particles.begin(), m_particles.end(), 
		[](Particle a, Particle b) -> float {return a.GetCamDistance() > b.GetCamDistance(); });
}

void ParticleSystem::Render(Camera& camera)
{
	glm::mat4 viewMat = camera.GetView();
	glm::vec3 vQuad1, vQuad2;
	glm::vec3 vView = camera.GetForwardVector();

	vView = glm::normalize(vView);
	vQuad1 = glm::cross(vView, camera.GetUpVector());
	vQuad1 = glm::normalize(vQuad1);
	vQuad2 = glm::cross(vView, vQuad1);
	vQuad2 = glm::normalize(vQuad2);

	glm::mat4 ProjView = camera.GetProjView();

	m_particleShader.Bind();
	m_particleShader.SetUniform3f("u_Quad1", vQuad1);
	m_particleShader.SetUniform3f("u_Quad2", vQuad2);
	m_particleShader.SetUniformMat4f("u_PV", ProjView);

	m_particleShader.SetUniform1i("u_tex", 0);
	m_particleTexture->Bind();

	glDepthMask(GL_FALSE);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_particlePositions.size(), &m_particlePositions[0], GL_DYNAMIC_DRAW);
	
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_NumParticles);
	glBindVertexArray(0);
	
	glDepthMask(GL_TRUE);
}
