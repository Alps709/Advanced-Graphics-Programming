#pragma once
#include "GameObject.h"

class TesselationObject : public GameObject
{
public:
	TesselationObject() = default;
	TesselationObject(glm::vec3 _position, glm::vec4 _colour);
	~TesselationObject();

	void SetShaderUniforms(Camera & _myCamera) const override;
	void Render(Camera & _myCamera) override;

	glm::vec4 m_colour;
};

