#include "TerrainMesh.h"
#include "FastNoise.h"

TerrainMesh::TerrainMesh(unsigned int _xSize = 128, unsigned int _zSize = 128)
{
	GenerateTerrainMesh(_xSize, _zSize);
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

void TerrainMesh::GenerateTerrainMesh(unsigned int _xSize, unsigned int _zSize)
{
	FastNoise noiseGenerator;
	noiseGenerator.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	noiseGenerator.SetFractalOctaves(4);
	noiseGenerator.SetFractalLacunarity(2.2f);

	const int SIZE = 1;
	const int noiseHeightMod = SIZE * 30;
	const int count = _xSize * _zSize;

	const float topLeftX = (_xSize - 1) / -2.0f;
	const float topLeftZ = (_zSize - 1) / 2.0f;

	std::vector<float> vertices(count * 8);

	std::vector<unsigned int> indices((_xSize - 1) * (_zSize - 1) * 6);

	int vertexPointer = 0;

	for (unsigned int z = 0; z < _zSize; z++)
	{
		for (unsigned int x = 0; x < _xSize; x++)
		{
			float height = noiseGenerator.GetNoise((float)x, (float)z) * noiseHeightMod * -1;
			m_heightMap.push_back(height);

			//Positions
			vertices[vertexPointer]     = (float)(x * SIZE);
			vertices[vertexPointer + 1] = height;
			vertices[vertexPointer + 2] = (float)(z * SIZE);

			//Calculate the normals afterwards
			//Normals				
			//vertices[vertexPointer + 3] = 0;
			//vertices[vertexPointer + 4] = 1;
			//vertices[vertexPointer + 5] = 0;

			//Texture co-ords		
			vertices[vertexPointer + 6] = (float)x / (_xSize - 1) * 5; //We times by 5 here cause we want the texture to repeat 5 times 
			vertices[vertexPointer + 7] = (float)z / (_zSize - 1) * 5; //across the x and y of the mesh
			vertexPointer += 8;
		}
	}


	//Calculate normals
	float invTwoDX = 1.0f / (2.0f * SIZE);
	float invTwoDZ = 1.0f / (2.0f * SIZE);

	vertexPointer = 0;
	for (unsigned int z = 1; z < _zSize - 1; z++)
	{
		for (unsigned int x = 1; x < _xSize - 1; x++)
		{

			float top    = m_heightMap[(z - 1) * _zSize + x];
			float bottom = m_heightMap[(z + 1) * _zSize + x];
			float left   = m_heightMap[z * _zSize + x - 1];
			float right  = m_heightMap[z * _zSize + x + 1];
			
			//Calculate the tangentials
			glm::vec3 tanZ = glm::vec3(0.0f, (top - bottom) * invTwoDZ, 1.0f);
			glm::vec3 tanX = glm::vec3(0.0f, (right - left) * invTwoDX, 0.0f);
			
			//Calculate normal by finding the cross product
			glm::vec3 crossProduct = glm::cross(tanZ, tanX);
			crossProduct = glm::normalize(crossProduct);

			//Normals				
			vertices[vertexPointer + 3] = crossProduct.x;
			vertices[vertexPointer + 4] = crossProduct.y;
			vertices[vertexPointer + 5] = crossProduct.z;

			//Move to next vertex
			vertexPointer += 8;
		}
	}

	int countIndices = 0;
	int pointer = 0;
	for (unsigned int gz = 0; gz < _zSize - 1; gz++) 
	{
		for (unsigned int gx = 0; gx < _xSize - 1; gx++) 
		{
			indices[pointer]     = countIndices;
			indices[pointer + 1] = countIndices + _xSize;
			indices[pointer + 2] = countIndices + _xSize + 1;

			indices[pointer + 3] = countIndices + _xSize + 1;
			indices[pointer + 4] = countIndices + 1;
			indices[pointer + 5] = countIndices;

			pointer += 6;
			countIndices++;
		}
		countIndices++;
	}

	m_vertices = vertices;
	m_indices = indices;
}
