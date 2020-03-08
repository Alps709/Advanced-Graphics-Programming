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
	vbInfo.Push<unsigned>(2);

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
	noiseGenerator.SetNoiseType(FastNoise::Perlin);
	noiseGenerator.SetGradientPerturbAmp(50);
	
	const int SIZE = 800;
	const int count = _xSize * _zSize;

	const int topLeftX = (_xSize - 1) / -2.0f;
	const int topLeftZ = (_zSize - 1) / 2.0f;

	std::vector<float> vertices(count * 8);

	std::vector<unsigned int> indices((_xSize - 1) * (_zSize - 1) * 6);

	int vertexPointer = 0;

	int tempX = 0;
	int tempZ = 0;
	for (int z = 0; z < _zSize; z++)
	{
		//Variable of current x position to give to the noise generator
		tempZ = topLeftZ - z;

		for (int x = 0; x < _xSize; x++)
		{
			//Variable of current x position to give to the noise generator
			tempX = topLeftX + x;

			//Positions
			vertices[vertexPointer]     = tempX * SIZE;
			vertices[vertexPointer + 1] = noiseGenerator.GetNoise(tempX, tempZ) * 50;
			vertices[vertexPointer + 2] = tempZ * SIZE;
									
			//Normals				
			vertices[vertexPointer + 3] = 0;
			vertices[vertexPointer + 4] = 1;
			vertices[vertexPointer + 5] = 0;
									
			//Texture co-ords		
			vertices[vertexPointer + 6] = (float)x / ((float)_xSize - 1);
			vertices[vertexPointer + 7] = (float)z / ((float)_zSize - 1);
			vertexPointer += 8;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < _zSize - 1; gz++) 
	{
		for (int gx = 0; gx < _xSize - 1; gx++) 
		{
			if (gx < _zSize - 1 && gz < _xSize - 1)
			{
				indices[pointer]     = pointer;
				indices[pointer + 1] = pointer + _xSize + 1;
				indices[pointer + 2] = pointer + _zSize;

				indices[pointer + 3] = pointer + _xSize + 1;
				indices[pointer + 4] = pointer;
				indices[pointer + 5] = pointer + 1;

				pointer += 6;
			}
		}
	}

	m_vertices = vertices;
	m_indices = indices;
}
