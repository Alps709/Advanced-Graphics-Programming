#include "Bullet.h"

//Calls the base class constructor
Bullet::Bullet(SphereMesh* _sphereMesh, Shader* _shader, glm::vec3 _position, glm::vec3 _seekPos) : Object(_sphereMesh, _shader, _position)
{
	m_bulletClock.Initialise();
	cubeMap = &(CubeMap::getInstance());
	m_seekPos = _seekPos;
}

void Bullet::Render(Camera& _myCamera)
{
	//Bind the mesh that all the models will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	BindTexture(0);

	GLCall(glActiveTexture(GL_TEXTURE1));
	m_shader->SetUniform1i("u_skyBox", 1);
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->m_texID));

	//Set object specific uniforms
	SetShaderUniforms(_myCamera);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void *>(0)));

	Mesh::Unbind();
}

void Bullet::Process(float _deltaTime)
{
	m_velocity += Seek(m_seekPos);

	//Limit velocity based on game play state
	Math::LimitVector3D(m_velocity, m_maxSpeed);

	//Apply velocity to movement (affected by delta time)
	m_position += m_velocity * static_cast<float>(_deltaTime);

	//Update model matrix so the boid faces in the direction it is moving
	SetPRS(m_position.x, 0.0f, m_position.z, 50.0f, 50.0f, 50.0f, 50.0f);
}

void Bullet::SetShaderUniforms(Camera& _myCamera) const
{
	//Prepare renderer (eg. clear buffer, create PVM matrix etc.)
	glm::mat4 projViewMat = _myCamera.GetProjView();

	glm::mat4 pvmMat = projViewMat * m_modelMat;

	//Set object specific uniforms
	//m_shader->SetUniform1i("u_tex", 0);
	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniformMat4f("u_modelMat", const_cast<glm::mat4&>(m_modelMat));
	m_shader->SetUniform3f("u_camPos", _myCamera.GetPosition());
}

double Bullet::GetTimeAlive()
{
	m_bulletClock.Process();
	return m_bulletClock.GetTimeElapsedS();
}

glm::vec3 Bullet::Seek(glm::vec3 _target)
{
	//Calculate the desired vector
	glm::vec3 desiredVec = _target - m_position;

	//Limit the magnitude to max speed
	Math::LimitVector3D(desiredVec, m_maxSpeed);

	glm::vec3 steeringForce = desiredVec - m_velocity;

	return steeringForce;
}
