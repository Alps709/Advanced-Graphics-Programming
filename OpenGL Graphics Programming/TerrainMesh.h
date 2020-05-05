#pragma once
#include "VertexBufferInfo.h"
#include <glm.hpp>

class TerrainMesh
{
public:
	TerrainMesh() = default;
	TerrainMesh(unsigned int _xSize, unsigned int _zSize);
	~TerrainMesh();

	void GenerateTerrainMesh(unsigned int _xSize, unsigned int _zSize);

	void AddVAOBuffer(const VertexBufferInfo _info);
	void SetVertexAttributes();

	std::vector<float> GetTerrainHeights();
	unsigned int GetindicesCount() const { return m_indicesCount; }

	void Bind() const;
	static void Unbind();

private:

	GLuint m_vaoID{ 0 };
	GLuint m_vboID{ 0 };
	GLuint m_iboID{ 0 };

	const unsigned int m_verticesPerSide = 128;
	unsigned int m_xSize{};
	unsigned int m_zSize{};

	std::vector<float> m_heightMap{};
	std::vector<float> m_vertices{};
	std::vector<unsigned int> m_indices{};

	//Used by the renderer to know how many indices to draw
	unsigned int m_indicesCount{ 0 };
};

