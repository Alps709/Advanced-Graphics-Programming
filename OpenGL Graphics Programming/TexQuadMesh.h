#include "Mesh.h"

class TexQuadMesh : public Mesh
{
public:
	TexQuadMesh() = default;
	TexQuadMesh(std::vector<float> _vertices, std::vector<unsigned int> _indices);

	void SetVertexAttributes() override;
};
