#include "WaterTerrain.h"

#include "Mesh.h"

WaterTerrain::WaterTerrain(unsigned int _xSize, unsigned int _zSize, glm::vec3 _position, Texture* _terrainTexture, Texture* _noiseTexture)
	: Terrain(_xSize, _zSize, _position, _terrainTexture)
{
	m_shader = Shader("Shaders/TerrainWaterVS.glsl", "Shaders/TerrainWaterFS.glsl");
	m_tex1 = _noiseTexture;
}

void WaterTerrain::SetShaderUniforms(Camera& _myCamera, double _time, bool _fogRenderMode) const
{
	//Prepare renderer (eg. clear buffer, create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	glm::mat4 modelMat = m_modelMat;
	glm::vec3 camPos = _myCamera.GetPosition();

	//Set object specific uniforms
	m_shader.SetUniform1i("u_grassTex", 0);
	m_shader.SetUniform1i("u_perlinNoiseTex", 1);

	m_shader.SetUniform1i("u_fogRenderMode", _fogRenderMode);
			
	m_shader.SetUniform1f("u_time", (float)_time);
	m_shader.SetUniform3f("u_camPos", camPos);

	m_shader.SetUniformMat4f("u_PVM", pvmMat);
	m_shader.SetUniformMat4f("u_modelMat", modelMat);
}

void WaterTerrain::Render(Camera& _myCamera, double _time, bool _fogRenderMode)
{
	//Bind the mesh that all the model will use
	m_mesh->Bind();
	m_shader.Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera, _time, _fogRenderMode);

	//Bind grass texture
	BindTexture(0);

	//Bind noise texture
	BindTexture(1);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

	Mesh::Unbind();
	Shader::Unbind();
}
