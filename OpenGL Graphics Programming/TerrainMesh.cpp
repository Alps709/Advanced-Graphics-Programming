#include "TerrainMesh.h"

TerrainMesh::TerrainMesh(unsigned int _xSize, unsigned int _zSize)
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

	//4 colour floats
	//vbInfo.Push<float>(4);

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
	const unsigned int count = m_verticesPerSide * m_verticesPerSide;
	std::vector<Vertex> vertices(count * 3);
	//std::vector<float> colours(count * 4);
	std::vector<unsigned> indices(6 * (m_verticesPerSide - 1) * (m_verticesPerSide - 1));

	int vertexPointer = 0;
	Vertex tempVert{};
	for (int j = 0; j < _xSize; j++)
	{
		for (int i = 0; i < _zSize; i++)
		{
			tempVert.Position.x = (float)j / ((float)m_verticesPerSide - 1) * _xSize;
			tempVert.Position.y = 0;
			tempVert.Position.z = (float)i / ((float)m_verticesPerSide - 1) * _zSize;
			tempVert.Normal.x = 0;
			tempVert.Normal.y = 1;
			tempVert.Normal.z = 0;
			//textureCoords[vertexPointer * 2] = (float)j / ((float)m_xSize - 1);
			//textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)m_xSize - 1);

			vertices[vertexPointer] = tempVert;
			vertexPointer++;
		}
	}

	int pointer = 0;
	auto index = &indices[pointer];
	for (int gz = 0; gz < m_verticesPerSide - 1; gz++) 
	{
		for (int gx = 0; gx < m_verticesPerSide - 1; gx++) 
		{
			int topLeft = (gz * m_verticesPerSide) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * m_verticesPerSide) + gx;
			int bottomRight = bottomLeft + 1;
			*(index++) = topLeft;
			*(index++) = bottomLeft;
			*(index++) = topRight;
			*(index++) = topRight;
			*(index++) = bottomLeft;
			*(index++) = bottomRight;
		}
	}

	m_indices = indices;
}
