#pragma once
#include "Object.h"

class Cube : public Object
{
public:
	Cube() = default;
	Cube(glm::vec3 _position, Texture* _terrainTexture);
	~Cube();

	void SetShaderUniforms(Camera& _myCamera, bool _fogRenderMode, bool _stencilOutline) const;
	void Render(Camera& _myCamera, bool _fogRenderMode);
};

