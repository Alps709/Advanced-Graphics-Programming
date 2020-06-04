#include "Terrain.h"

#include "Math.h"

#include "GameObject.h"
#include "Camera.h"

Terrain::Terrain(unsigned int _xSize, unsigned int _zSize, glm::vec3 _position, bool _genNoiseTex)
{
	m_xSize = _xSize;
	m_zSize = _zSize;

	std::vector<float>* heightMapData{};

	if (_genNoiseTex)
	{
		m_perlinNoiseTexture = m__noiseTexGenerator.GenerateTexture();
		heightMapData = m__noiseTexGenerator.GetPixelData();
	}

	m_mesh = new TerrainMesh(_xSize, _zSize, heightMapData);
	m_grassShader = Shader("Shaders/TerrainG_0_VS.glsl", "Shaders/TerrainG_1_TCS.glsl", "Shaders/TerrainG_2_TES.glsl", "Shaders/TerrainG_3_GS.glsl", "Shaders/TerrainG_4_FS.glsl");
	m_baseShader = Shader("Shaders/Terrain_0_VS.glsl", "Shaders/Terrain_1_TCS.glsl", "Shaders/Terrain_2_TES.glsl", "Shaders/Terrain_3_FS.glsl");
	m_position = _position;
	m_tex0 = new Texture("Resources/Textures/terrainTex.png", 0);
	m_tex1 = new Texture("Resources/Textures/grassTexS.png", 1);

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

float Terrain::GetTerrainHeight(float _worldX, float _worldZ)
{
	auto heights = m_mesh->GetTerrainHeights();

	//Get the x and y relative to the terrain
	float localX = _worldX - m_position.x;
	float localZ = _worldZ - m_position.z;

	//Size of 1 square in world space (1) divided by the number of vertices in the terrain along one side minus 1
	//This gives the number of grid squares along the X side
	float gridSquaresSize = 1;

	int gridX = (int)floorf(localX / gridSquaresSize);
	int gridZ = (int)floorf(localZ / gridSquaresSize);

	if (gridX >= (int)(sqrtf(float(heights.size())) - 1) || gridZ >= (int)(sqrtf(float(heights.size())) - 1) || gridX <= 0 || gridZ <= 0)
	{
		//Not on the terrain
		return 0;
	}
	 
	//Find the coordinates within the grid square (0 - 1)
	float xCoord = fmod(localX, gridSquaresSize) / gridSquaresSize;
	float zCoord = fmod(localZ, gridSquaresSize) / gridSquaresSize;

	float answer = 0;
	
	if (zCoord <= 1 - xCoord)
	{
		//In first triangle of the grid square
		answer = Math::BarryCentricInterp(glm::vec3(0, heights[gridZ * m_zSize + gridX], 0), 
			glm::vec3(1, heights[gridZ * m_zSize + gridX + 1], 0),
			glm::vec3(0, heights[(gridZ + 1) * m_zSize + gridX], 1),
			glm::vec2(xCoord, zCoord));
	}
	else
	{
		//In second triangle of the grid square
		answer = Math::BarryCentricInterp(glm::vec3(1, heights[gridZ * m_zSize + gridX + 1],       0),
										  glm::vec3(1, heights[(gridZ + 1) * m_zSize + gridX + 1], 1),
										  glm::vec3(0, heights[(gridZ + 1) * m_zSize + gridX],     1),
										  glm::vec2(xCoord, zCoord));
	}

	return answer;
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

//This empty implementation is needed so that the linker can have base classes can override it
void Terrain::SetShaderUniforms(Camera& _myCamera, double _time, bool _fogRenderMode) const
{
}

//This empty implementation is needed so that the linker can have base classes can override it
void Terrain::Render(Camera& _myCamera, double _time, bool _fogRenderMode)
{
}

void Terrain::SetShaderUniforms(Camera& _myCamera, double _time, bool _fogRenderMode, bool _grassRenderMode) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvMat = _myCamera.GetProjView();
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	glm::mat4 modelMat = m_modelMat;
	glm::vec3 camPos = _myCamera.GetPosition();

	if(_grassRenderMode)
	{
		//Set object specific uniforms
		m_grassShader.SetUniform1i("u_terrainTex", 0);
		m_grassShader.SetUniform1i("u_grassTex", 1);
		m_grassShader.SetUniform1i("u_heightMapTex", 2);
		m_grassShader.SetUniformMat4f("u_PV", pvMat);
		m_grassShader.SetUniformMat4f("u_PVM", pvmMat);
		m_grassShader.SetUniformMat4f("u_modelMat", modelMat);
		m_grassShader.SetUniform3f("u_cameraPos", camPos);
		m_grassShader.SetUniform1i("u_fogRenderMode", _fogRenderMode);
	}
	else
	{
		//Set object specific uniforms
		m_baseShader.SetUniform1i("u_terrainTex", 0);
		m_grassShader.SetUniform1i("u_heightMapTex", 2);
		m_grassShader.SetUniformMat4f("u_PV", pvMat);
		m_baseShader.SetUniformMat4f("u_modelMat", modelMat);
		m_baseShader.SetUniform3f("u_cameraPos", camPos);
		m_baseShader.SetUniform1i("u_fogRenderMode", _fogRenderMode);
	}
}

void Terrain::Render(Camera& _myCamera, double _time, bool _fogRenderMode, bool _grassRenderMode) const
{
	//Bind the mesh that all the model will use
	m_mesh->Bind();

	if(_grassRenderMode)
	{
		m_grassShader.Bind();
		BindTexture(0);
		BindTexture(1);
		BindTexture(2);
	}
	else
	{
		m_baseShader.Bind();
		BindTexture(0);
		BindTexture(2);
	}
	
	//Prepare the object for drawing
	SetShaderUniforms(_myCamera, _time, _fogRenderMode, _grassRenderMode);

	//Tells opengl that the tessellation patches are triangles
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	GLCall(glDisable(GL_CULL_FACE));
	
	//Draw the object
	GLCall(glDrawElements(GL_PATCHES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

	GLCall(glEnable(GL_CULL_FACE));

	Texture::Unbind();
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
	else if (_texNum == 2)
	{
		m_perlinNoiseTexture->Bind();
	}
}
