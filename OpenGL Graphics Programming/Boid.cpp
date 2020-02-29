#include "Boid.h"

//Calls the base class constructor
Boid::Boid(SphereMesh* _sphereMesh, Shader* _shader, glm::vec3 _position) : Object(_sphereMesh, _shader, _position)
{
	m_boidClock.Initialise();
	cubeMap = &(CubeMap::getInstance());
}

void Boid::Render(Camera& _myCamera)
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

void Boid::Process(glm::vec3 _tankPos, float _deltaTime)
{
	//Get the acceleration vector that is seeking towards the tank position
	m_acceleration += Seek(glm::vec3(_tankPos.x, 0.0f, _tankPos.z));

	//Apply acceleration
	Math::LimitVector3D(m_acceleration, m_maxAcceleration);

	m_velocity += m_acceleration;

	//Limit velocity based on game play state
	Math::LimitVector3D(m_velocity, m_maxSpeed);

	//Apply velocity to movement (affected by delta time)
	m_position += m_velocity * static_cast<float>(_deltaTime);

	//Reset acceleration every update
	m_acceleration *= 0.0f;

	//Update model matrix so the boid faces in the direction it is moving
	SetPRS(m_position.x, 0.0f, m_position.z, 0.0f, 50.0f, 50.0f, 50.0f);
}

void Boid::SetShaderUniforms(Camera& _myCamera) const
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

double Boid::GetTimeAlive()
{
	m_boidClock.Process();
	return m_boidClock.GetTimeElapsedS();
}

glm::vec3 Boid::Seek(glm::vec3 _target)
{
	//Calculate the desired vector
	glm::vec3 desiredVec = _target - m_position;

	//Limit the magnitude to max speed
	Math::LimitVector3D(desiredVec, m_maxSpeed);

	glm::vec3 steeringForce = desiredVec - m_velocity;

	Math::LimitVector3D(steeringForce, m_maxForce);

	return steeringForce;
}
