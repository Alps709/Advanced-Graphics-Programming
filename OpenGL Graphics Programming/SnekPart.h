#pragma once
#include "Object.h"
#include "SphereMesh.h"

class SnekPart final : public Object
{
public:
	SnekPart(SphereMesh* _sphereMesh, Shader* _shader, glm::vec3 _position);
	~SnekPart() = default;
	
	void Render(Camera& _myCamera) override;
	void SetShaderUniforms(Camera& _myCamera) const override;
	double GetRadius() const override { return m_snekColliderRadius; }

	double m_snekColliderRadius = 20.0f;
};

