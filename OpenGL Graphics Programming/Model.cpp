#include "Model.h"
#include "Math.h"

Model::Model(std::string path, Shader* shader)
{
	m_shader = shader;

	this->loadModel(path);
}

void Model::SetPosition(glm::vec3 _pos)
{
	m_position = _pos;

	//Update the stored model matrix
	UpdateModelMat();
}

void Model::ChangePRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ)
{
	m_position += glm::vec3(_translateX, _translateY, _translateZ);

	//Add new rotation and cap it to 360
	m_rotationY += _rotationAngle;
	m_rotationY = fmod(m_rotationY, 360.0f);

	m_scale += glm::vec3(_scaleX, _scaleY, _scaleZ);

	//Update the stored model matrix
	UpdateModelMat();
}

void Model::SetPRS(float _translateX, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ)
{
	m_position = glm::vec3(_translateX, 0, _translateZ);

	//Add new rotation and cap it to 360
	m_rotationY = _rotationAngle;
	m_rotationY = fmod(m_rotationY, 360.0f);

	m_scale = glm::vec3(_scaleX, _scaleY, _scaleZ);

	//Update the stored model matrix
	UpdateModelMat();
}

void Model::UpdateModelMat()
{
	//Update the stored model matrix
	m_modelMat = Math::Create2DModelMatrix(m_position.x, m_position.y, m_position.z, m_rotationY, m_scale.x, m_scale.y, m_scale.z);
}

void Model::Render(Camera& _camera)
{
	//Prepare renderer (eg. clear buffer, create PVM matrix etc.)
	glm::mat4 projViewMat = _camera.GetProjView();

	glm::mat4 pvmMat = projViewMat * m_modelMat;

	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		//printf("mesh size: %d \n", meshes.size());
		this->meshes[i].Render(pvmMat, m_shader);
	}
}
