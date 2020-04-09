#include "Terrain.h"

#include "Math.h"

#include "Object.h"
#include "Camera.h"

Terrain::Terrain(unsigned int _xSize, unsigned int _zSize, glm::vec3 _position, Texture* _terrainTexture)
{
	m_mesh = new TerrainMesh(_xSize, _zSize);
	m_shader = Shader("Shaders/TerrainVS.glsl", "Shaders/TerrainFS.glsl");
	m_position = _position;
	m_tex0 = _terrainTexture;

	//SetScale(glm::vec3(200.0f, 200.0f, 200.0f));

	//Update the stored model matrix
	UpdateModelMat();
}

Terrain::~Terrain()
{
	delete m_mesh;
}

void Terrain::SetPosition(glm::vec3 _pos)
{
	m_position = _pos;

	//Update the stored model matrix
	UpdateModelMat();
}

void Terrain::SetScale(glm::vec3 _scale)
{
	m_scale = _scale;
}

void Terrain::SetTexture0(Texture* _tex)
{
	m_tex0 = _tex;
}

void Terrain::SetTexture1(Texture* _tex)
{
	m_tex1 = _tex;
}

void Terrain::ChangePRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ)
{
	m_position += glm::vec3(_translateX, _translateY, _translateZ);

	//Add new rotation and cap it to 360
	m_rotationZ += _rotationAngle;
	m_rotationZ = fmod(m_rotationZ, 360.0f);

	m_scale += glm::vec3(_scaleX, _scaleY, _scaleZ);

	//Update the stored model matrix
	UpdateModelMat();
}

void Terrain::SetPRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ)
{
	m_position = glm::vec3(_translateX, _translateY, _translateZ);

	//Add new rotation and cap it to 360
	m_rotationZ = _rotationAngle;
	m_rotationZ = fmod(m_rotationZ, 360.0f);

	m_scale = glm::vec3(_scaleX, _scaleY, _scaleZ);

	//Update the stored model matrix
	UpdateModelMat();
}

void Terrain::UpdateModelMat()
{
	//Update the stored model matrix
	m_modelMat = Math::Create2DModelMatrix(m_position.x, m_position.y, m_position.z, m_rotationZ, m_scale.x, m_scale.y, m_scale.z);
}

void Terrain::SetShaderUniforms(Camera& _myCamera, double _time, bool _fogRenderMode) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	glm::mat4 modelMat = m_modelMat;
	glm::vec3 camPos = _myCamera.GetPosition();

	//Set object specific uniforms
	m_shader.SetUniform1i("u_grassTex", 0);
	m_shader.SetUniformMat4f("u_PVM", pvmMat);
	m_shader.SetUniformMat4f("u_modelMat", modelMat);
	m_shader.SetUniform3f("u_camPos", camPos);
	m_shader.SetUniform1i("u_fogRenderMode", _fogRenderMode);
}

void Terrain::Render(Camera& _myCamera, double _time, bool _fogRenderMode)
{
	//Bind the mesh that all the model will use
	m_mesh->Bind();
	m_shader.Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera, _time, _fogRenderMode);

	//Bind grass texture
	BindTexture(0);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

	Mesh::Unbind();
	Shader::Unbind();
}

void Terrain::BindTexture(unsigned int _texNum) const
{
	//Meant to be expanded if the object needs more than one texture
	if (_texNum == 0)
	{
		m_tex0->Bind();
	}
	else if (_texNum == 1)
	{
		m_tex1->Bind();
	}
}
