#include "TerrainMesh.h"
#include "FastNoise.h"

TerrainMesh::TerrainMesh(unsigned int _xSize = 128, unsigned int _zSize = 128, std::vector<float>* _heightMapData = nullptr)
{
	GenerateTerrainMesh(_xSize, _zSize, _heightMapData);
	m_indicesCount = m_indices.size();

	//Generate vao
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glBindVertexArray(m_vaoID));

	//Generate vbo
	GLCall(glGenBuffers(1, &m_vboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), static_cast<const void*>(m_vertices.data()), GL_STATIC_DRAW));

	//Generate ibo
	GLCall(glGenBuffers(1, &m_iboID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(unsigned int), static_cast<const void*>(m_indices.data()), GL_STATIC_DRAW));

	SetVertexAttributes();
	Unbind();
}

void TerrainMesh::AddVAOBuffer(const VertexBufferInfo _info)
{
	const auto& indices = _info.Getindices();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < indices.size(); ++i)
	{
		const auto element = indices[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, (element.normalised ? GL_TRUE : GL_FALSE), _info.GetStride(), reinterpret_cast<const void*>(offset)));
		offset += element.count * VBElementInfo::GetTypeSize(element.type);
	}
}

void TerrainMesh::SetVertexAttributes()
{
	//Create layout and populate it with the vertex attribute information
	VertexBufferInfo vbInfo;

	//3 m_position floats
	vbInfo.Push<float>(3);

	//3 normal floats
	vbInfo.Push<float>(3);

	//2 tex co-ord ints
	vbInfo.Push<float>(2);

	AddVAOBuffer(vbInfo);
}

std::vector<float> TerrainMesh::GetTerrainHeights() const
{
	return m_heightMap;
}

void TerrainMesh::Bind() const
{
	//Bind vao
	GLCall(glBindVertexArray(m_vaoID));
}

void TerrainMesh::Unbind()
{
	GLCall(glBindVertexArray(0));
}

TerrainMesh::~TerrainMesh()
{
}

void TerrainMesh::GenerateTerrainMesh(unsigned int _xSize, unsigned int _zSize, std::vector<float>* _heightMapData)
{
	bool useHeightMapData = false;
	if(_heightMapData != nullptr)
	{
		useHeightMapData = true;
	}
	
	FastNoise noiseGenerator;
	noiseGenerator.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	noiseGenerator.SetFractalOctaves(3);
	noiseGenerator.SetFractalLacunarity(2.2f);
	noiseGenerator.SetFrequency(1);

	const float SIZE = 128.0f / _zSize;
	const float noiseHeightMod = 30;
	const int count = _xSize * _zSize;

	//const float topLeftX = (_xSize - 1) / -2.0f;
	//const float topLeftZ = (_zSize - 1) / 2.0f;

	std::vector<float> vertices(count * 8);
	m_heightMap = std::vector<float>(count);

	std::vector<unsigned int> indices((_xSize - 1) * (_zSize - 1) * 6);

	unsigned int vertexIndex = 0;

	//Size the of the texture (in this case hard coded 4096) divided by the zSize of the terrain
	//This gives us the multiplier to what y index of the heightmap to get
	const int textureWidth = 4096;
	int hmZIdxMult = 4096 / _zSize;
	int hmXIdxMult = 4096 / _xSize;
	for (unsigned int x = 0; x < _xSize; x++)
	{
		const int temp = 42;
		
		for (unsigned int z = 0; z < _zSize; z++)
		{
			//Get the height from the x,z from the Perlin noise function
			float height;
			if(useHeightMapData) 
			{
				//Get the index of the 4k x 4k texture as though it's _zSize x _zSize
				const int index = (z * hmZIdxMult) * (textureWidth) + (x * hmXIdxMult);
				height = (*_heightMapData)[index];
				height *= static_cast<float>(noiseHeightMod);
			}
			else
			{
				height = noiseGenerator.GetNoise(static_cast<float>(z)/_xSize, static_cast<float>(x)/_zSize) * noiseHeightMod * -1;
			} 

			m_heightMap[z * _zSize + x] = height;

			//Positions
			vertices[vertexIndex]     = static_cast<float>(x * SIZE);
			vertices[vertexIndex + 1] = height;
			vertices[vertexIndex + 2] = static_cast<float>(z * SIZE);

			//Calculate the normals afterwards
			//Normals				
			//vertices[vertexIndex + 3] = 0;
			//vertices[vertexIndex + 4] = 1;
			//vertices[vertexIndex + 5] = 0;

			//Texture co-ords		
			vertices[vertexIndex + 6] = static_cast<float>(x) / (_xSize + 1) + (1.0f / _xSize);
			vertices[vertexIndex + 7] = static_cast<float>(z) / (_zSize + 1) + (1.0f / _zSize);
			vertexIndex += 8;
		}
	}


	//Calculate normals
	vertexIndex = 0;
	for (unsigned int x = 1; x < _xSize - 1; x++)
	{
		for (unsigned int z = 1; z < _xSize - 1; z++)
		{

			float top    = m_heightMap[(z - 1) * _zSize + x];
			float bottom = m_heightMap[(z + 1) * _zSize + x];
			float left   = m_heightMap[z * _zSize + x - 1];
			float right  = m_heightMap[z * _zSize + x + 1];

			glm::vec3 normal = glm::vec3(left - right, 2.0f, bottom - top);
			glm::normalize(normal);

			//Normal			
			vertices[vertexIndex + 3] = normal.x;
			vertices[vertexIndex + 4] = normal.y;
			vertices[vertexIndex + 5] = normal.z;

			//Move to next vertex
			vertexIndex += 8;
		}
	}

	int countIndices = 0;
	unsigned int index = 0;
	for (unsigned int gx = 0; gx < _xSize - 1; gx++) 
	{
		for (unsigned int gz = 0; gz < _zSize - 1; gz++) 
		{
			indices[index]     = countIndices;
			indices[index + 1] = countIndices + _xSize + 1;
			indices[index + 2] = countIndices + _xSize;

			indices[index + 3] = countIndices + _xSize + 1;
			indices[index + 4] = countIndices;
			indices[index + 5] = countIndices + 1;

			index += 6;
			countIndices++;
		}
		countIndices++;
	}

	m_vertices = vertices;
	m_indices = indices;
}
