#include "TexQuadMesh.h"

TexQuadMesh::TexQuadMesh(std::vector<float> _vertices, std::vector<unsigned> _indices)
{
	m_vertices = _vertices;
	m_indicesCount = _indices.size();

	//Generate vao
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glBindVertexArray(m_vaoID));

	//Generate vbo
	GLCall(glGenBuffers(1, &m_vboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), static_cast<const void*>(_vertices.data()), GL_STATIC_DRAW));

	//Generate ibo
	GLCall(glGenBuffers(1, &m_iboID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(unsigned int), static_cast<const void*>(_indices.data()), GL_STATIC_DRAW));

	SetVertexAttributes();
}

void TexQuadMesh::SetVertexAttributes()
{
	//Create layout and populate it with the vertex attribute information
	VertexBufferInfo vbInfo;

	//3 m_position floats
	vbInfo.Push<float>(3);

	//2 texture co-ord floats
	vbInfo.Push<float>(2);

	AddVAOBuffer(vbInfo);
}
