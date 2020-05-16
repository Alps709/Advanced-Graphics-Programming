#include "Mesh.h"

Mesh::Mesh(std::vector<float> _vertices, std::vector<unsigned int> _indices)
{
	m_vertices = _vertices;
	m_indicesCount = _indices.size();

	//Tells opengl that if this is going to be using a tessellation shader, then it will tessellate quads
	glPatchParameteri(GL_PATCH_VERTICES, 4);

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
	Unbind();
}

Mesh::Mesh(std::vector<float> _vertices)
{
	m_vertices = _vertices;
	m_indicesCount = _vertices.size() / 3;
	
	//Generate vao
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glBindVertexArray(m_vaoID));

	//Generate vbo
	GLCall(glGenBuffers(1, &m_vboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), static_cast<const void*>(_vertices.data()), GL_STATIC_DRAW));

	SetVertexSingleAttribute();
	Unbind();
}

void Mesh::AddVAOBuffer(const VertexBufferInfo _info)
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

void Mesh::SetVertexAttributes()
{
	//Create layout and populate it with the vertex attribute information
	VertexBufferInfo vbInfo;

	//3 m_position floats
	vbInfo.Push<float>(3);

	//4 colour floats
	vbInfo.Push<float>(4);

	//2 texture co-ord floats
	vbInfo.Push<float>(2);

	AddVAOBuffer(vbInfo);
}

void Mesh::SetVertexSingleAttribute()
{
	//Create layout and populate it with the vertex attribute information
	VertexBufferInfo vbInfo;

	//3 m_position floats
	vbInfo.Push<float>(3);

	AddVAOBuffer(vbInfo);
}

void Mesh::Bind() const
{
	//Bind vao
	GLCall(glBindVertexArray(m_vaoID));
}

void Mesh::Unbind()
{
	GLCall(glBindVertexArray(0));
}

Mesh::~Mesh()
{
}
