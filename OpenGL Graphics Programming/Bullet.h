#pragma once
#include "Object.h"
#include "SphereMesh.h"
#include "clock.h"
#include "CubeMap.h"
#include "Math.h"
#include <random>

class Bullet : public Object
{
public:
	Bullet() = default;
	Bullet(SphereMesh* _sphereMesh, Shader* _shader, glm::vec3 _position, glm::vec3 _seekPos);
	~Bullet() = default;

	void Render(Camera& _myCamera) override;

	void Process(float _deltaTime);

	//Set custom uniforms
	void SetShaderUniforms(Camera& _myCamera) const;

	void ApplyForces(glm::vec3 _force);

	double GetRadius() const override { return m_bulletColliderRadius; }
	double GetTimeAlive();

	glm::vec3 Seek(glm::vec3 _target);

private:
	CClock m_bulletClock;
	double m_bulletColliderRadius = 50.0f;

	CubeMap* cubeMap;

	int m_boidID;

	glm::vec3 m_seekPos;

	glm::vec3 m_velocity;

	float m_maxSpeed = 10.0f;
};

