#pragma once
#include "Object.h"
#include "clock.h"
#include <random>

class Boid final : public Object
{
public:

	Boid(Mesh* _mesh, Shader* _shader, glm::vec3 _position);
	~Boid() = default;

	void Render(Camera& _myCamera) override;

	//Set custom uniforms
	void SetShaderUniforms(glm::mat4 _pvm) const;

	double GetRadius() const override { return m_pillColliderRadius; }
	double GetTimeAlive();

private:
	CClock m_pillClock;
	double m_pillColliderRadius = 10.0f;
};

