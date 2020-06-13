#include "ParticleSystemCS.h"

#include <algorithm>


#include "Camera.h"
#include <ctime>

//Generates a random float from 0 - 1
static float randomFloat()
{
	const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}

ParticleSystemCS::ParticleSystemCS(glm::vec3 _position, float _radius)
{
	m_computeShader = Shader("Shaders/ParticleCompute_0_CS.glsl");
	m_particleShader = Shader("Shaders/Particle_0_VS.glsl", "Shaders/Particle_1_GS.glsl", "Shaders/Particle_2_FS.glsl");
	m_particleTexture = new Texture("Resources/Textures/Snowflake.png", 0);

	m_originalPosition = _position;
	m_circleRadius = _radius;

	//Allocate the memory for the particles and a vector of their positions used for the vbo
	m_InitialPosition.resize(m_NumParticles);
	m_InitialVelocity.resize(m_NumParticles);

#pragma omp parallel for
	for (int i = 0; i < (int)m_NumParticles; i++)
	{
		m_InitialPosition[i] = glm::vec4(0.0f, 0.0f, 0.0f, 0.125f + randomFloat());

		m_InitialVelocity[i] = glm::vec4(//vel x
										 2.5f * cos(i * .0167f) * randomFloat() * 10.0f,
									 	 //vel y
										 10.0f + randomFloat() * 20.0f,
										 //vel z
										 2.5f * sin(i * .0167f) * randomFloat() * 10.0f,
										 //Time alive
										 1.0f + randomFloat() * 4.0f);
	}

	glGenBuffers(1, &m_posVbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_posVbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_InitialPosition.size() * sizeof(glm::vec4), &m_InitialPosition[0], GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_posVbo);

	glGenBuffers(1, &m_velVbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_velVbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_InitialVelocity.size() * sizeof(glm::vec4), &m_InitialVelocity[0], GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_velVbo);
	
	glGenBuffers(1, &m_initVelVbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_initVelVbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_InitialVelocity.size() * sizeof(glm::vec4), &m_InitialVelocity[0], GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_initVelVbo);

	glGenVertexArrays(1, &m_particleVao);
	glBindVertexArray(m_particleVao);

	glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, NULL, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ParticleSystemCS::~ParticleSystemCS()
{
	delete m_particleTexture;
}


void ParticleSystemCS::Update(float _deltaTime)
{
	const float deltaTimeMS = static_cast<float>(_deltaTime) * 0.001f;
	m_timer += deltaTimeMS;
	
	m_position = glm::vec3((m_circleRadius * sin(static_cast<float>(m_timer))) + m_originalPosition.x,
						   m_originalPosition.y,
						   (m_circleRadius * cos(static_cast<float>(m_timer))) + m_originalPosition.z);
	
	//Run computer shader first
	m_computeShader.Bind();

	m_computeShader.SetUniform3f("u_gravity", glm::vec3(0.0f, -9.8f, 0.0f) * deltaTimeMS);
	m_computeShader.SetUniform1f("u_deltaTime", deltaTimeMS);
	m_computeShader.SetUniform3f("u_particleSystemPos", m_position);
	
	glDispatchCompute(m_NumParticles / 128, 1, 1);

	//Wait for it to finish
	glMemoryBarrier(GL_ALL_BARRIER_BITS);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleSystemCS::Render(Camera& camera)
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
	glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, NULL, 0);
	glEnableVertexAttribArray(0);
	
	glDrawArrays(GL_POINTS, 0, m_NumParticles);
	
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Shader::Unbind();
	glDepthMask(GL_TRUE);
}