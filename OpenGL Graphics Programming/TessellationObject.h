#pragma once
#include "GameObject.h"

class TessellationObject : public GameObject
{
public:
	TessellationObject() = default;
	TessellationObject(glm::vec3 _position, glm::vec4 _colour);
	~TessellationObject();

	void SetShaderUniforms(Camera & _myCamera) const override;
	void Render(Camera & _myCamera) override;

	glm::vec4 m_colour;
};

