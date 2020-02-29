#pragma once
#include "Object.h"
#include "SphereMesh.h"
#include "clock.h"
#include "CubeMap.h"
#include "Math.h"
#include <random>

class Boid final : public Object
{
public:

	Boid() = default;
	Boid(SphereMesh* _sphereMesh, Shader* _shader, glm::vec3 _position);
	~Boid() = default;
	//Boid(const Boid&);
	void Render(Camera& _myCamera) override;

	void Process(glm::vec3 _tankPos, float _deltaTime);

	//Set custom uniforms
	void SetShaderUniforms(Camera& _myCamera) const;

	void ApplyForces(glm::vec3 _force);

	double GetRadius() const override { return m_boidColliderRadius; }
	double GetTimeAlive();

	glm::vec3 Seek(glm::vec3 _target);

private:
	CClock m_boidClock;
	double m_boidColliderRadius = 50.0f;

	CubeMap* cubeMap;

	int m_boidID;

	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	glm::vec3 m_force;

	float m_maxSpeed = 5.0f;

	float m_maxAcceleration = 0.04f;

	float m_maxForce = 0.01f;
};

