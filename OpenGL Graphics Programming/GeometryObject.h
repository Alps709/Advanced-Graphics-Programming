#pragma once
#include "GameObject.h"

class GeometryObject : public GameObject
{
public:
	GeometryObject() = default;
	GeometryObject(glm::vec3 _position, glm::vec4 _colour);
	~GeometryObject();

	void SetShaderUniforms(Camera & _myCamera) const override;
	void Render(Camera & _myCamera) override;

	glm::vec4 m_colour;
};

