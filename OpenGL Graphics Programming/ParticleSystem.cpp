#include "ParticleSystem.h"

#include <ctime>

//Generates a random float from 0 - 1
static float randomFloat()
{
	const float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}

ParticleSystem::ParticleSystem(glm::vec3 _position)
{
	m_NumParticles = 4000;
	for (int i = 0; i < m_NumParticles; i++)
	{
		m_particlePositions.emplace_back(0.0);
		
		//initialize position vector
		Particle p = Particle(m_position,

							  //vel x
							  glm::vec3(0.25 * cos(i * .0167) + 0.25f * randomFloat() - 0.125f,
							  //vel y
							  2.0f + 0.25f * randomFloat() - 0.125f,
							  //vel z
							0.25 * sin(i* .0167) + 0.25f * randomFloat() - 0.125f),

                              //Gravity val 
							  -2.0f,

                              // lifetime 
			                  randomFloat() + 0.125,

                              //id
							  i); 

		//Add the new particle to the vector
		particles.push_back(p);
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	glGenVertexArrays(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_particlePositions.size(), &m_particlePositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0); glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); glBindVertexArray(0);

}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Render(Camera& camera, float _deltaTime)
{
	//Update partcles and their positions for the VBO
	for (int i = 0; i < m_NumParticles; i++)
	{
		m_particles[i].Update(_deltaTime);
		m_particlePositions[i] = m_particles[i].GetPosition();
	}
	glm::mat4 viewMat = camera.GetView();
	glm::vec3 vQuad1, vQuad2;
	vQuad1 = camera.GetUpVector();
	vQuad2 = camera.GetRightVector();

	glm::mat4 ProjView = camera.GetProjView();

	m_particleShader.Bind();
	m_particleShader.SetUniform3f("u_Quad1", vQuad1.x, vQuad1.y, vQuad1.z);
	m_particleShader.SetUniform3f("u_Quad2", vQuad2.x, vQuad2.y, vQuad2.z);
	m_particleShader.SetUniformMat4f("u_PV", ProjView);

	m_particleShader.SetUniform1i("u_tex", 0);
	m_particleTexture.Bind();

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_particlePositions.size(), &m_particlePositions[0], GL_STATIC_DRAW);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_NumParticles);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE); glDisable(GL_BLEND);
}
